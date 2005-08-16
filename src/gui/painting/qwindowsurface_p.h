/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QWINDOWSURFACE_P_H
#define QWINDOWSURFACE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/qwidget.h>

class QPaintDevice;
class QRegion;
class QRect;
class QPoint;
class QImage;
class QWindowSurfacePrivate;

class Q_GUI_EXPORT QWindowSurface
{
public:
    QWindowSurface(QWidget *window);
    virtual ~QWindowSurface();

    QWidget *window() const;

    virtual QPaintDevice *paintDevice() = 0;
    virtual void flush(QWidget *widget, const QRegion &region,
                       const QPoint &offset) = 0;
    virtual void setGeometry(const QRect &rect);
    QRect geometry() const;

    virtual bool scroll(const QRegion &area, int dx, int dy);

    virtual void beginPaint(const QRegion &);
    virtual void endPaint(const QRegion &);

    virtual QImage* buffer(const QWidget *widget);
    virtual QPixmap grabWidget(const QWidget *widget, const QRect& rectangle = QRect()) const;

    virtual QPoint offset(const QWidget *widget) const;
    inline QRect rect(const QWidget *widget) const;

private:
    QWindowSurfacePrivate *d_ptr;
};

QRect QWindowSurface::rect(const QWidget *widget) const
{
    return widget->rect().translated(offset(widget));
}

#endif // QWINDOWSURFACE_P_H
