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

#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <qtextbrowser.h>

class MainWindow;
class QKeyEvent;
class QMime;
class QMouseEvent;
class QMenu;

class HelpWindow : public QTextBrowser
{
    Q_OBJECT
public:
    HelpWindow( MainWindow *m, QWidget *parent = 0);
    void setSource( const QUrl &name );
    void blockScrolling( bool b );
    void openLinkInNewWindow( const QString &link );
    void openLinkInNewPage( const QString &link );
    void addMimePath( const QString &path );

    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *);

    bool isBackwardAvailable() const { return backAvail; }
    bool isForwardAvailable() const { return fwdAvail; }
    void updateFormat();

signals:
    void chooseWebBrowser();
    void choosePDFReader();

protected:
    virtual void contextMenuEvent(QContextMenuEvent *e);

protected slots:
    void ensureCursorVisible();

private slots:
    void openLinkInNewWindow();
    void openLinkInNewPage();
    void updateForward(bool);
    void updateBackward(bool);

    bool isKDERunning() const;

private:
    MainWindow *mw;
    QString lastAnchor;
    bool blockScroll;
    bool shiftPressed;
    bool newWindow;
    bool fwdAvail;
    bool backAvail;
};

#endif
