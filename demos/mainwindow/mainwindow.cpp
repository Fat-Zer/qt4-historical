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

#include "mainwindow.h"

#include "colorswatch.h"
#include "toolbar.h"

#include <qaction.h>
#include <qlayout.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qstatusbar.h>
#include <qtextedit.h>

static const char * const message =
    "<p><b>Qt Main Window Demo</b></p>"

    "<p>This is a demonstration of the QMainWindow, QToolBar and "
    "QDockWidget classes.</p>"

    "<p>The tool bar and dock widgets can be dragged around and rearranged "
    "using the mouse or via the menu.</p>"

    "<p>Each dock widget contains a colored frame and a context "
    "(right-click) menu.</p>"

#ifdef Q_WS_MAC
    "<p>On Mac OS X, the \"Black\" dock widget has been created as a "
    "<em>Drawer</em>, which is a special kind of QDockWidget.</p>"
#endif
    ;

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("Qt Main Window Demo");

    setupToolBar();
    setupMenuBar();
    setupDockWidgets();

    QTextEdit *center = new QTextEdit(this);
    center->setReadOnly(true);
    center->setHtml(tr(message));
    center->setMinimumSize(400, 205);
    setCentralWidget(center);

    statusBar()->showMessage(tr("Status Bar"));
}

void MainWindow::actionTriggered(QAction *action)
{
    qDebug("action '%s' triggered", action->text().toLocal8Bit().data());
}

void MainWindow::setupToolBar()
{
    toolbar = new ToolBar(this);
    toolbar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBar(toolbar);
}

void MainWindow::setupMenuBar()
{
    QMenu *menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(tr("&Quit"), this, SLOT(close()));

    menuBar()->addMenu(toolbar->menu);
    dockWidgetMenu = menuBar()->addMenu(tr("&Dock Widgets"));
}

void MainWindow::setupDockWidgets()
{
    static const struct Set {
        const char * name;
        uint flags;
        Qt::DockWidgetArea area;
    } sets [] = {
#ifndef Q_WS_MAC
        { "Black", 0, Qt::LeftDockWidgetArea },
#else
        { "Black", Qt::Drawer, Qt::LeftDockWidgetArea },
#endif
        { "White", 0, Qt::RightDockWidgetArea },
        { "Red", 0, Qt::TopDockWidgetArea },
        { "Green", 0, Qt::TopDockWidgetArea },
        { "Blue", 0, Qt::BottomDockWidgetArea },
        { "Yellow", 0, Qt::BottomDockWidgetArea }
    };
    const int setCount = sizeof(sets) / sizeof(Set);

    for (int i = 0; i < setCount; ++i) {
        ColorSwatch *swatch = new ColorSwatch(tr(sets[i].name), this, Qt::WFlags(sets[i].flags));
        addDockWidget(sets[i].area, swatch);
        dockWidgetMenu->addMenu(swatch->menu);
    }
}
