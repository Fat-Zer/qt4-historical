/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
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

    bool execute(QString program, QString arguments = QString(), int timeout = -1, int *returnValue = NULL);
private:
    bool connected;
};

#endif
