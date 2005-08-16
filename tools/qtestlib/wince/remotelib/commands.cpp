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
#include "commands.h"

#define CLEAN_FAIL(a) {delete appName; \
    delete arguments; \
    return (a); }

int qRemoteLaunch(DWORD, BYTE*, DWORD*, BYTE**, IRAPIStream* stream)
{
    if (!stream)
        return -1;

    DWORD bytesRead;
    int appLength;
    wchar_t* appName = 0;
    int argumentsLength;
    wchar_t* arguments = 0;
    bool waitForFinished = 0;
    int returnValue = -2;

    if (S_OK != stream->Read(&appLength, sizeof(appLength), &bytesRead))
        CLEAN_FAIL(-2);
    appName = (wchar_t*) malloc(sizeof(wchar_t)*(appLength + 1));
    if (S_OK != stream->Read(appName, sizeof(wchar_t)*appLength, &bytesRead))
        CLEAN_FAIL(-2);
    appName[appLength] = '\0';

    if (S_OK != stream->Read(&argumentsLength, sizeof(argumentsLength), &bytesRead))
        CLEAN_FAIL(-2);
    arguments = (wchar_t*) malloc(sizeof(wchar_t)*(argumentsLength + 1));
    if (S_OK != stream->Read(arguments, sizeof(wchar_t)*argumentsLength, &bytesRead))
        CLEAN_FAIL(-2);
    arguments[argumentsLength] = '\0';

    if (S_OK != stream->Read(&waitForFinished, sizeof(waitForFinished), &bytesRead))
        CLEAN_FAIL(-2);

    bool result = qRemoteExecute(appName, arguments, &returnValue, true);

    if (waitForFinished) {
        if (S_OK != stream->Write(&returnValue, sizeof(returnValue), &bytesRead))
            CLEAN_FAIL(-4);
    }
    delete appName;
    delete arguments;
    // We need to fail here for the execute, otherwise the calling application will wait
    // forever for the returnValue.
    if (!result)
        return -3;
    return S_OK;
}


bool qRemoteExecute(const wchar_t* program, const wchar_t* arguments, int *returnValue, bool waitForFinished)
{
    if (!program)
        return false;

    PROCESS_INFORMATION pid;
    if (!CreateProcess(program, arguments, NULL, NULL, false, 0, NULL, NULL, NULL, &pid)) {
        wprintf(L"Could not launch: %s\n", program);
        return false;
    }

    if (waitForFinished) {
        if (WAIT_OBJECT_0 == WaitForSingleObject(pid.hProcess, INFINITE) && returnValue) {
            *returnValue = 0;
            DWORD exitCode;
            if (GetExitCodeProcess(pid.hProcess, &exitCode))
                *returnValue = exitCode;
        }
    }

    return true;
}
