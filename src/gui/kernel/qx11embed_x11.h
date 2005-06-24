/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the gui module of the Qt Toolkit.
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

#ifndef QX11EMBED_H
#define QX11EMBED_H

#include <QtGui/qwidget.h>

class QX11EmbedWidgetPrivate;
class QX11EmbedWidget : public QWidget
{
    Q_OBJECT
public:
    QX11EmbedWidget(QWidget *parent = 0);
    ~QX11EmbedWidget();

    void embedInto(WId id);
    WId containerWinId() const;

    enum Error {
	Unknown,
	Internal,
	InvalidWindowID
    };
    Error error() const;
   
signals:
    void embedded();
    void containerClosed();
    void error(Error error);
    
protected:
    bool x11Event(XEvent *);
    bool eventFilter(QObject *, QEvent *);
    bool event(QEvent *);
    void resizeEvent(QResizeEvent *);
    
private:
    Q_DECLARE_PRIVATE(QX11EmbedWidget)
    Q_DISABLE_COPY(QX11EmbedWidget)
};

class QX11EmbedContainerPrivate;
class QX11EmbedContainer : public QWidget
{
    Q_OBJECT
public:
    QX11EmbedContainer(QWidget *parent = 0);
    ~QX11EmbedContainer();
        
    void embedClient(WId id);
    void discardClient();

    WId clientWinId() const;

    QSize minimumSizeHint() const;
    
    enum Error {
	Unknown,
	Internal,
	InvalidWindowID
    };
    Error error() const;

signals:
    void clientIsEmbedded();
    void clientClosed();
    void error(Error);
    
protected:
    bool x11Event(XEvent *);
    bool eventFilter(QObject *, QEvent *);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    bool event(QEvent *);
    
private:
    Q_DECLARE_PRIVATE(QX11EmbedContainer)
    Q_DISABLE_COPY(QX11EmbedContainer)
};

#endif
