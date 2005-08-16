/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the assistant application of the Qt Toolkit.
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

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <qdialog.h>

#include "ui_finddialog.h"

class MainWindow;
class QStatusBar;
class QTextBrowser;

class FindDialog : public QDialog
{
    Q_OBJECT
public:
    FindDialog(MainWindow *parent);
    virtual ~FindDialog();

    MainWindow *mainWindow() const;
    bool hasFindExpression() const;

public slots:
    void reset();
    void doFind(bool forward);
    void statusMessage(const QString &message);

private slots:
    void findButtonClicked();    

private:
    Ui::FindDialog ui;
    QWidget *contentsWidget;

    QStatusBar *sb;
    bool onceFound;
    QString findExpr;
    QTextBrowser *lastBrowser;
};

#endif

