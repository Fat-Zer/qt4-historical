/****************************************************************************
**
** Copyright (C) 2004-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef RSSLISTING_H
#define RSSLISTING_H

#include <QHttp>
#include <QWidget>
#include <QBuffer>
#include <QXmlStreamReader>
class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;

class RSSListing : public QWidget
{
    Q_OBJECT
public:
    RSSListing(QWidget *widget = 0);

public slots:
    void fetch();
    void finished(int id, bool error);
    void readData(const QHttpResponseHeader &);

private:
    void parseXml();

    QXmlStreamReader xml;
    QString currentTag;
    QString linkString;
    QString titleString;

    QHttp http;
    int connectionId;

    QLineEdit *lineEdit;
    QTreeWidget *treeWidget;
    QPushButton *abortButton;
    QPushButton *fetchButton;
};

#endif

