/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. 
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "remoteconnection.h"
#include <qdir.h>
#include <qfile.h>
#include <qfileinfo>
#include <rapi.h>

extern void debugOutput(const QString& text, int level);

bool RemoteConnection::connect()
{
    if (connected)
        return true;
    connected = false;
    RAPIINIT init;
    init.cbSize = sizeof(init);
    if (CeRapiInitEx(&init) != S_OK)
        return connected;

    DWORD res;
    res = WaitForMultipleObjects(1,&(init.heRapiInit),true, 5000);
    if ((res == -1) || (res == WAIT_TIMEOUT) || (init.hrRapiInit != S_OK))
        return connected;

    connected = true;
    return connected;
}

void RemoteConnection::disconnect()
{
    connected = false;
    CeRapiUninit();
}

bool RemoteConnection::copyFileToDevice(const QString &localSource, const QString &deviceDest, bool failIfExists)
{
    if (failIfExists) {
        CE_FIND_DATA search;
        HANDLE searchHandle = CeFindFirstFile(deviceDest.utf16(), &search);
        if (searchHandle != INVALID_HANDLE_VALUE) {
            CeFindClose(searchHandle);
            return false;
        }
    }

    QFile file(localSource);
    if (!file.exists())
        return false;
    if (!file.open(QIODevice::ReadOnly)) {
        debugOutput(QString::fromLatin1("  Could not open source file"),2);
        if (file.size() == 0) {
            // Create an empy file
            deleteFile(deviceDest);
            HANDLE deviceHandle = CeCreateFile(deviceDest.utf16(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
            if (deviceHandle != INVALID_HANDLE_VALUE) {
                CeCloseHandle(deviceHandle);
                return true;
            }
        }
        return false;
    }

    deleteFile(deviceDest);
    HANDLE deviceHandle = CeCreateFile(deviceDest.utf16(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (deviceHandle == INVALID_HANDLE_VALUE) {
        debugOutput(QString::fromLatin1("  Could not create target file"), 2);
        return false;
    }

    DWORD written = 0;
    int currentPos = 0;
    int size = file.size();
    DWORD toWrite = 0;
    const int bufferSize = 65000;
    QByteArray data;
    data.reserve(bufferSize);
    while (currentPos < size) {
        data = file.read(bufferSize);
        if (data.size() <= 0) {
            wprintf( L"Error while reading file!\n");
            return false;
        }
        if (size - currentPos > bufferSize )
            toWrite = bufferSize;
        else
            toWrite = size - currentPos;
        if (toWrite == 0)
            break;
        if (!CeWriteFile(deviceHandle, data.data() , toWrite, &written, NULL)) {
            debugOutput(QString::fromLatin1("  Could not write File"), 2);
            return false;
        }
        currentPos += written;
        data.clear();
        wprintf( L"%s -> %s (%d / %d) %d %%\r", localSource.utf16() , deviceDest.utf16(), currentPos , size, (100*currentPos)/size );
    }
    wprintf(L"\n");

    // Copy FileTime for update verification
    FILETIME creationTime, accessTime, writeTime;
    HANDLE localHandle = CreateFile(localSource.utf16(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    if (localHandle != INVALID_HANDLE_VALUE) {
        if (GetFileTime(localHandle, &creationTime, &accessTime, &writeTime)) {
            LocalFileTimeToFileTime(&writeTime, &writeTime);
            if (!CeSetFileTime(deviceHandle, &writeTime, NULL, NULL)) {
                debugOutput(QString::fromLatin1("  Could not write time values"), 0);
            }
        }
        CloseHandle(localHandle);
    }
    CeCloseHandle(deviceHandle);

    DWORD attributes = GetFileAttributes(localSource.utf16());
    if (attributes != -1 )
        CeSetFileAttributes(deviceDest.utf16(), attributes);
    return true;
}

bool RemoteConnection::copyDirectoryToDevice(const QString &localSource, const QString &deviceDest, bool recursive)
{
    QDir dir(localSource);
    if (!dir.exists())
        return false;

    deleteDirectory(deviceDest, recursive);
    CeCreateDirectory(deviceDest.utf16(), NULL);
    foreach(QString entry, dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot)) {
        QString source = localSource + "\\" + entry;
        QString target = deviceDest + "\\" + entry;
        QFileInfo info(source);
        if (info.isDir()) {
            if (recursive) {
                if (!copyDirectoryToDevice(source, target, recursive))
                    return false;
            }
        } else {
            if (!copyFileToDevice(source, target))
                return false;
        }
    }
    return true;
}

bool RemoteConnection::copyFileFromDevice(const QString &deviceSource, const QString &localDest, bool failIfExists)
{
    QFile target(localDest);
    if (failIfExists && target.exists()) {
        debugOutput(QString::fromLatin1("  Not allowed to overwrite file"), 2);
        return false;
    }

    if (target.exists())
        target.remove();

    HANDLE deviceHandle = CeCreateFile(deviceSource.utf16(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    if (deviceHandle == INVALID_HANDLE_VALUE) {
        debugOutput(QString::fromLatin1("  Could not open file on device"), 2);
        return false;
    }

    DWORD fileSize = CeGetFileSize( deviceHandle, NULL );
    if (fileSize == -1) {
        debugOutput(QString::fromLatin1("  Could not stat filesize of remote file"), 2);
        CeCloseHandle(deviceHandle);
        return false;
    }

    if (!target.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        debugOutput(QString::fromLatin1("  Could not open local file for writing"), 2);
        CeCloseHandle(deviceHandle);
        return false;
    }

    int bufferSize = 65000;
    char *buffer = (char*) malloc(bufferSize);
    DWORD bufferRead = 0;
    DWORD bufferWritten = 0;
    bool readUntilEnd = false;
    while(CeReadFile(deviceHandle, buffer, bufferSize, &bufferRead, NULL)) {
        if (bufferRead == 0) {
            readUntilEnd = true;
            break;
        }
        target.write(buffer, bufferRead);
        bufferWritten += bufferRead;
        wprintf(L"%s -> %s (%d / %d) %d %%\r", deviceSource.utf16(), localDest.utf16(), bufferWritten, fileSize, (100*bufferWritten)/fileSize);
    }
    wprintf(L"\n");

    if (!readUntilEnd) {
        debugOutput(QString::fromLatin1("  an error occured during copy"), 2);
        return false;
    }

    CeCloseHandle(deviceHandle);
    return true;
}
 
bool RemoteConnection::copyDirectoryFromDevice(const QString &deviceSource, const QString &localDest, bool recursive)
{
    if (!QDir(localDest).exists() && !QDir(localDest).mkpath(QDir(localDest).absolutePath())) {
        debugOutput(QString::fromLatin1("  Could not create local path"), 2);
    }

    QString searchArg = deviceSource + "\\*";
    CE_FIND_DATA data;
    HANDLE searchHandle = CeFindFirstFile(searchArg.utf16(), &data);
    if (searchHandle == INVALID_HANDLE_VALUE) {
        // We return true because we might be in a recursive call
        // where nothing is to copy and the copy process
        // might still be correct
        return true;
    }

    do {
        QString srcFile = deviceSource + "\\" + QString::fromUtf16(data.cFileName);
        QString destFile = localDest + "\\" + QString::fromUtf16(data.cFileName);
        if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            if (recursive && !copyDirectoryFromDevice(srcFile, destFile, recursive)) {
                wprintf(L"Copy of subdirectory(%s) failed\n", srcFile.utf16());
                return false;
            }
        } else {
            copyFileFromDevice(srcFile, destFile, false);
        }
    } while(CeFindNextFile(searchHandle, &data));
    CeFindClose(searchHandle);
    return true;
}

bool RemoteConnection::copyFile(const QString &srcFile, const QString &destFile, bool failIfExists)
{
    return CeCopyFile(QDir::toNativeSeparators(srcFile).utf16(), 
                      QDir::toNativeSeparators(destFile).utf16(), failIfExists);
}

bool RemoteConnection::copyDirectory(const QString &srcDirectory, const QString &destDirectory,
                                      bool recursive)
{
    CeCreateDirectory(destDirectory.utf16(), NULL);
    QString searchArg = srcDirectory + "\\*";
    CE_FIND_DATA data;
    HANDLE searchHandle = CeFindFirstFile(searchArg.utf16(), &data);
    if (searchHandle == INVALID_HANDLE_VALUE) {
        // We return true because we might be in a recursive call
        // where nothing is to copy and the copy process
        // might still be correct
        return true;
    }

    do {
        QString srcFile = srcDirectory + "\\" + QString::fromUtf16(data.cFileName);
        QString destFile = destDirectory + "\\" + QString::fromUtf16(data.cFileName);
        if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            if (recursive && !copyDirectory(srcFile, destFile, recursive)) {
                wprintf(L"Copy of subdirectory(%s) failed\n", srcFile.utf16());
                return false;
            }
        } else {
            debugOutput(QString::fromLatin1("Copy %1 -> %2\n").arg(srcFile).arg(destFile), 0);
            CeCopyFile(srcFile.utf16(), destFile.utf16(), false);
        }
    } while(CeFindNextFile(searchHandle, &data));
    CeFindClose(searchHandle);
    return true;
}

void RemoteConnection::deleteFile(const QString &fileName)
{
    CeSetFileAttributes(fileName.utf16(), FILE_ATTRIBUTE_NORMAL);
    CeDeleteFile(fileName.utf16());
    return;
}

void RemoteConnection::deleteDirectory(const QString &directory, bool recursive)
{
    HANDLE hFind;
    CE_FIND_DATA FindFileData;
    QString FileName = directory + "\\*";
    hFind = CeFindFirstFile(FileName.utf16(), &FindFileData);
    if( hFind == INVALID_HANDLE_VALUE ) {
        CeRemoveDirectory(directory.utf16());
        return;
    }
    do {
        QString FileName = directory + "\\" + QString::fromUtf16(FindFileData.cFileName);
        if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            if (recursive)
                deleteDirectory(FileName);
        } else {
            if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                CeSetFileAttributes(FileName.utf16(), FILE_ATTRIBUTE_NORMAL);
            if( !CeDeleteFile(FileName.utf16()) )
                break;
        }
    } while(CeFindNextFile(hFind,&FindFileData));
    CeFindClose(hFind);

    CeRemoveDirectory(directory.utf16());
    return;
}

bool RemoteConnection::execute(QString program, QString arguments, bool waitUntilFinished, int *returnValue)
{
    if (!isConnected()) {
        qWarning("Cannot execute, connect to device first!");
        return false;
    }

    PROCESS_INFORMATION* pid = new PROCESS_INFORMATION;
    bool result = false;
    if (waitUntilFinished) {
        // If we want to wait, we have to use CeRapiInvoke, as CeCreateProcess has no way to wait
        // until the process ends. The lib must have been build and also deployed already.
        if (!isConnected() && !connect())
            return false;

        QString dllLocation = "\\Windows\\QtRemote.dll";
        QString functionName = "qRemoteLaunch";

        DWORD outputSize;
        BYTE* output;
        IRAPIStream *stream;
        int returned = 0;
        HRESULT res = CeRapiInvoke(dllLocation.utf16(), functionName.utf16(), 0, 0, &outputSize, &output, &stream, 0);
        if (S_OK != res) {
            if (S_OK != CeGetLastError())
                debugOutput(QString::fromLatin1("Error: Could not invoke method on QtRemote"),1);
            else
                debugOutput(QString::fromLatin1("Error: QtRemote return unexpectedly with error Code %1").arg(res), 1);
        } else {
            DWORD written;
            int strSize = program.length();
            if (S_OK != stream->Write(&strSize, sizeof(strSize), &written)) {
                qWarning("   Could not write appSize to process");
                return false;
            }
            if (S_OK != stream->Write(program.utf16(), program.length()*sizeof(wchar_t), &written)) {
                qWarning("   Could not write appName to process");
                return false;
            }
            strSize = arguments.length();
            if (S_OK != stream->Write(&strSize, sizeof(strSize), &written)) {
                qWarning("   Could not write argumentSize to process");
                return false;
            }
            if (S_OK != stream->Write(arguments.utf16(), arguments.length()*sizeof(wchar_t), &written)) {
                qWarning("   Could not write arguments to process");
                return false;
            }
            if (S_OK != stream->Write(&waitUntilFinished, sizeof(waitUntilFinished), &written)) {
                qWarning("   Could not write waiting option to process");
                return false;
            }

            if (S_OK != stream->Read(&returned, sizeof(returned), &written)) {
                qWarning("   Could not access return value of process");
            }
            result = true;
        }


        if (returnValue)
            *returnValue = returned;
    } else {
        // We do not need to invoke another lib etc, if we are not interested in results anyway...
        result = CeCreateProcess(program.utf16(), arguments.utf16(), 0, 0, false, 0, 0, 0, 0, pid);
    }
    return result;
}

bool RemoteConnection::createDirectory(const QString &path, bool deleteBefore)
{
    if (deleteBefore)
        deleteDirectory(path);
    QStringList separated = path.split(QLatin1Char('\\'));
    QString current = QLatin1String("\\");
    bool result;
    for (int i=1; i < separated.size(); ++i) {
        current += separated.at(i);
        result = CeCreateDirectory(current.utf16(), NULL);
        current += QLatin1String("\\");
    }
    return result;
}

