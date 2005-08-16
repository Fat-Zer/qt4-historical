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

#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QDialog>

class QFile;
class QHttp;
class QHttpResponseHeader;
class QLabel;
class QLineEdit;
class QProgressDialog;
class QPushButton;

class HttpWindow : public QDialog
{
    Q_OBJECT

public:
    HttpWindow(QWidget *parent = 0);

private slots:
    void downloadFile();
    void cancelDownload();
    void httpRequestFinished(int requestId, bool error);
    void readResponseHeader(const QHttpResponseHeader &responseHeader);
    void updateDataReadProgress(int bytesRead, int totalBytes);
    void enableDownloadButton();

private:
    QLabel *statusLabel;
    QLabel *urlLabel;
    QLineEdit *urlLineEdit;
    QProgressDialog *progressDialog;
    QPushButton *quitButton;
    QPushButton *downloadButton;

    QHttp *http;
    QFile *file;
    int httpGetId;
    bool httpRequestAborted;
};

#endif
