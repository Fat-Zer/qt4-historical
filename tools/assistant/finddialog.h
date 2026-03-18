/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Assistant of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
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
#include <qstandarditemmodel.h>

class MainWindow;
class QStatusBar;
class QTextBrowser;

class CaseSensitiveModel : public QStandardItemModel
{
public:
    CaseSensitiveModel(int rows, int columns, QObject *parent = 0);
    QModelIndexList match(const QModelIndex &start, int role, const QVariant &value, int hits, Qt::MatchFlags flags) const;
};

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

