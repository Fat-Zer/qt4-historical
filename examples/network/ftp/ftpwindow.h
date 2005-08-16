/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef FTPWINDOW_H
#define FTPWINDOW_H

#include <QDialog>
#include <QHash>

class QFile;
class QFtp;
class QLabel;
class QLineEdit;
class QListWidget;
class QListWidgetItem;
class QProgressDialog;
class QPushButton;
class QUrlInfo;

class FtpWindow : public QDialog
{
    Q_OBJECT

public:
    FtpWindow(QWidget *parent = 0);

private slots:
    void connectToFtpServer();
    void downloadFile();
    void cancelDownload();

    void ftpCommandFinished(int commandId, bool error);
    void addToList(const QUrlInfo &urlInfo);
    void processItem(QListWidgetItem *item);
    void cdToParent();
    void updateDataTransferProgress(qint64 readBytes,
                                    qint64 totalBytes);
    void enableConnectButton();
    void enableDownloadButton();

private:
    QLabel *ftpServerLabel;
    QLineEdit *ftpServerLineEdit;
    QLabel *statusLabel;
    QListWidget *fileList;
    QPushButton *quitButton;
    QPushButton *connectButton;
    QPushButton *downloadButton;
    QPushButton *cdToParentButton;
    QProgressDialog *progressDialog;

    QHash<QString, bool> isDirectory;
    QString currentPath;
    QFtp *ftp;
    QFile *file;
};

#endif
