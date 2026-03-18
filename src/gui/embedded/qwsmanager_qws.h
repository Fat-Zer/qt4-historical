/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QWSMANAGER_QWS_H
#define QWSMANAGER_QWS_H

#include "QtGui/qpixmap.h"
#include "QtCore/qobject.h"
#include "QtGui/qdecoration_qws.h"
#include "QtGui/qevent.h"

QT_MODULE(Gui)

#ifndef QT_NO_QWS_MANAGER

class QAction;
class QPixmap;
class QWidget;
class QPopupMenu;
class QRegion;
class QMouseEvent;
class QWSManagerPrivate;

class QWSManager : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWSManager)
public:
    explicit QWSManager(QWidget *);
    ~QWSManager();

    static QDecoration *newDefaultDecoration();

    QWidget *widget();
    static QWidget *grabbedMouse();
    void maximize();
    void startMove();
    void startResize();

    QRegion region();
    QRegion &cachedRegion();

protected slots:
    void menuTriggered(QAction *action);

protected:
    void handleMove(QPoint g);

    virtual bool event(QEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void paintEvent(QPaintEvent *);
    bool repaintRegion(int region, QDecoration::DecorationState state);

    void menu(const QPoint &);

private:
    friend class QWidget;
    friend class QWidgetPrivate;
    friend class QApplication;
    friend class QApplicationPrivate;
};

#include "QtGui/qdecorationdefault_qws.h"

#endif // QT_NO_QWS_MANAGER

#endif // QWSMANAGER_QWS_H
