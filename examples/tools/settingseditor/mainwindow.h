/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class QSettings;
class LocationDialog;
class SettingsTree;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void openSettings();
    void openIniFile();
    void openPropertyList();
    void openRegistryPath();
    void about();

private:
    void createActions();
    void createMenus();
    void setSettingsObject(QSettings *settings);

    SettingsTree *settingsTree;
    LocationDialog *locationDialog;

    QMenu *fileMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QAction *openSettingsAct;
    QAction *openIniFileAct;
    QAction *openPropertyListAct;
    QAction *openRegistryPathAct;
    QAction *refreshAct;
    QAction *exitAct;
    QAction *autoRefreshAct;
    QAction *fallbacksAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif
