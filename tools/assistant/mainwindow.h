/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the assistant application of the Qt Toolkit.
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <qpointer.h>
#include <qmap.h>

class TabbedBrowser;
class HelpDialog;
class FindDialog;
class SettingsDialog;
class HelpWindow;
class QMenu;
class QDockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

    TabbedBrowser *browsers() const;
    HelpDialog *helpDialog() const;

    void setupPopupMenu(QMenu *menu);
    static QString urlifyFileName(const QString &fileName);

public slots:
    MainWindow *newWindow();

    void setup();
    void showLink(const QString &link);
    void showLinks(const QStringList &links);
    void saveSettings();
    void updateBookmarkMenu();

private slots:
    void on_actionNewWindow_triggered();
    void on_actionGoHome_triggered();
    void on_actionEditFind_triggered();
    void on_actionEditFindAgain_triggered();
    void on_actionEditFindAgainPrev_triggered();
    void on_actionFilePrint_triggered();
    void on_actionSettings_triggered();
    void on_actionClose_triggered();
    void on_actionHelpWhatsThis_triggered();
    void on_actionHelpAssistant_triggered();
    void on_actionAboutApplication_triggered();
    void on_actionAboutAssistant_triggered();
    void on_actionSaveAs_triggered();

    void about();
    void setupBookmarkMenu();
    void showBookmark(QAction *action);
    void showLinkFromClient(const QString &link);
    void showQtHelp();
    void showWebBrowserSettings();
    void showPDFReaderSettings();
    void showSettingsDialog(int page);
    void showSearchLink(const QString &link, const QStringList &terms);
    void showGoActionLink();
    void updateProfileSettings();
    void backwardAvailable(bool);
    void forwardAvailable(bool);

    void browserTabChanged();

protected:
    void closeEvent(QCloseEvent *);
    void timerEvent(QTimerEvent *);

private:
    void setupGoActions();
    bool insertActionSeparator();

private:
    Ui::MainWindow ui;

    QList<QAction*> goActions;
    uint setupCompleted:1;
    TabbedBrowser *tabs;
    SettingsDialog *settingsDia;
    QMap<QAction*, QString> bookmarks;
    HelpDialog *helpDock;
    QDockWidget *dw;
    QPointer<FindDialog> findDialog;
    static QList<MainWindow*> windows;
    QMap<QAction*,QString> *goActionDocFiles;
    QStringList pendingLinks;
    QList<HelpWindow*> pendingBrowsers;
};

#endif // MAINWINDOW_H
