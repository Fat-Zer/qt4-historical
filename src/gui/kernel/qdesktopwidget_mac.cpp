/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the gui module of the Qt Toolkit.
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

#include "qapplication.h"
#include "qdesktopwidget.h"
#include <private/qt_mac_p.h>
#include "qwidget_p.h"

/*****************************************************************************
  Externals
 *****************************************************************************/
RgnHandle qt_mac_get_rgn(); //qregion_mac.cpp
void qt_mac_dispose_rgn(RgnHandle r); //qregion_mac.cpp

/*****************************************************************************
  QDesktopWidget member functions
 *****************************************************************************/
class QDesktopWidgetPrivate : public QWidgetPrivate
{
public:
    QDesktopWidgetPrivate();

    int appScreen;
    int screenCount;

    QVector<GDHandle> devs;
    QVector<QRect> rects;
};

QDesktopWidgetPrivate::QDesktopWidgetPrivate()
{
    appScreen = screenCount = 0;
    for(GDHandle g = GetMainDevice(); g; g = GetNextDevice(g))
        screenCount++;
    devs.resize(screenCount);
    rects.resize(screenCount);
    int i = 0;
    for(GDHandle g = GetMainDevice(); i < screenCount && g; g = GetNextDevice(g), i++) {
        devs[i] = g;
        Rect r = (*g)->gdRect;
        rects[i] = QRect(r.left, r.top, r.right - r.left, r.bottom - r.top);
    }
}

QDesktopWidget::QDesktopWidget()
: QWidget(*new QDesktopWidgetPrivate, 0, Qt::Desktop)
{
    setObjectName("desktop");
    setAttribute(Qt::WA_WState_Visible);
}

QDesktopWidget::~QDesktopWidget()
{
}

bool QDesktopWidget::isVirtualDesktop() const
{
    return true;
}

int QDesktopWidget::primaryScreen() const
{
    return d_func()->appScreen;
}

int QDesktopWidget::numScreens() const
{
    return d_func()->screenCount;
}

QWidget *QDesktopWidget::screen(int)
{
    return this;
}

const QRect QDesktopWidget::availableGeometry(int screen) const
{
    Q_D(const QDesktopWidget);
    if(screen < 0 || screen >= d->screenCount)
        screen = d->appScreen;
    Rect r;
    GetAvailableWindowPositioningBounds(d->devs[screen], &r);
    return QRect(r.left, r.top, r.right - r.left, r.bottom - r.top);
}

const QRect QDesktopWidget::screenGeometry(int screen) const
{
    Q_D(const QDesktopWidget);
    if(screen < 0 || screen >= d->screenCount)
        screen = d->appScreen;
    return d->rects[screen];
}

int QDesktopWidget::screenNumber(const QWidget *widget) const
{
    Q_D(const QDesktopWidget);
    if(!widget)
        return d->appScreen;
    QRect frame = widget->frameGeometry();
    if(!widget->isWindow())
        frame.moveTopLeft(widget->mapToGlobal(QPoint(0,0)));
    int maxSize = -1, maxScreen = -1;
    for(int i = 0; i < d->screenCount; ++i) {
        QRect sect = d->rects[i].intersect(frame);
        int size = sect.width() * sect.height();
        if(size > maxSize && sect.width() > 0 && sect.height() > 0) {
            maxSize = size;
            maxScreen = i;
        }
    }
    return maxScreen;
}

int QDesktopWidget::screenNumber(const QPoint &point) const
{
    Q_D(const QDesktopWidget);
    int closestScreen = -1;
    int shortestDistance = INT_MAX;
    for (int i = 0; i < d->screenCount; ++i) {
        int thisDistance = d->pointToRect(point, d->rects.at(i));
        if (thisDistance < shortestDistance) {
            shortestDistance = thisDistance;
            closestScreen = i;
        }
    }
    return closestScreen;
}

void QDesktopWidget::resizeEvent(QResizeEvent *)
{
    Q_D(QDesktopWidget);
    QDesktopWidgetPrivate *old_d = d;
    d_ptr = new QDesktopWidgetPrivate;
    for(int i = 0; i < d->screenCount; i++) {
        if(i > old_d->screenCount || d->rects[i] != old_d->rects[i])
            emit resized(i);
    }
    delete old_d;
}
