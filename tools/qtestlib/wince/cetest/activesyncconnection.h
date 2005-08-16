/****************************************************************************
**
** Copyright (C) 2008-2008 Trolltech ASA. All rights reserved.
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

#ifndef ACTIVESYNC_REMOTECONNECTION_H
#define ACTIVESYNC_REMOTECONNECTION_H

#include "remoteconnection.h"

#if defined(Q_OS_WIN32)
#define REMOTELIBNAME "remotecommands"
#endif

class ActiveSyncConnection : public AbstractRemoteConnection
{
public:
    ActiveSyncConnection();
    virtual ~ActiveSyncConnection();

    bool connect(QVariantList &list = QVariantList());
    void disconnect();
    bool isConnected() const;

    // These functions are designed for transfer between desktop and device
    // Caution: deviceDest path has to be device specific (eg. no drive letters for CE)
    bool copyFileToDevice(const QString &localSource, const QString &deviceDest, bool failIfExists = false);
    bool copyDirectoryToDevice(const QString &localSource, const QString &deviceDest, bool recursive = true);
    bool copyFileFromDevice(const QString &deviceSource, const QString &localDest, bool failIfExists = false);
    bool copyDirectoryFromDevice(const QString &deviceSource, const QString &localDest, bool recursive = true);

    bool timeStampForLocalFileTime(FILETIME*) const;
    bool fileCreationTime(const QString &fileName, FILETIME*) const;

    // These functions only work on files existing on the device
    bool copyFile(const QString&, const QString&, bool failIfExists = false);
    bool copyDirectory(const QString&, const QString&, bool recursive = true);
    bool deleteFile(const QString&);
    bool deleteDirectory(const QString&, bool recursive = true, bool failIfContentExists = false);
    bool moveFile(const QString&, const QString&, bool FailIfExists = false);
    bool moveDirectory(const QString&, const QString&, bool recursive = true);

    bool createDirectory(const QString&, bool deleteBefore=false);

    bool execute(QString program, QString arguments = QString(), bool waitUntilFinished = true, int *returnValue = NULL);
private:
    bool connected;
};

#endif
