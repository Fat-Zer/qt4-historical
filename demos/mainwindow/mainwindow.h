/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ToolBar;
class QMenu;
class QSignalMapper;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ToolBar *toolbar;
    QMenu *dockWidgetMenu;
    QSignalMapper *mapper;

public:
    MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

public slots:
    void actionTriggered(QAction *action);
    void saveLayout();
    void loadLayout();
    void setCorner(int id);
    void switchLayoutDirection();

private:
    void setupToolBar();
    void setupMenuBar();
    void setupDockWidgets();
};

#endif
