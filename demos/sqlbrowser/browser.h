/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <qwidget.h>
#include "ui_browserwidget.h"

class ConnectionWidget;
class QTableView;
class QPushButton;
class QTextEdit;

class Browser: public QWidget, private Ui::Browser
{
    Q_OBJECT
public:
    Browser(QWidget *parent = 0);
    virtual ~Browser();

public slots:
    void exec();
    void showTable(const QString &table);
    void addConnection();

    void on_connectionWidget_tableActivated(const QString &table)
    { showTable(table); }
    void on_submitButton_clicked() {
        exec();
        sqlEdit->setFocus();
    }
    void on_clearButton_clicked() {
        sqlEdit->clear();
        sqlEdit->setFocus();
    }

signals:
    void statusMessage(const QString &message);
};

#endif
