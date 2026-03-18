/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>

class ToolBar;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ToolBar *toolbar;
    QMenu *dockWidgetMenu;

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);

public slots:
    void actionTriggered(QAction *action);

private:
    void setupToolBar();
    void setupMenuBar();
    void setupDockWidgets();
};

#endif
