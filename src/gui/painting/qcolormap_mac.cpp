/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
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

#include "qcolormap.h"
#include "qcolor.h"


class QColormapPrivate
{
public:
    inline QColormapPrivate()
        : ref(0)
    { }

    QAtomic ref;
};
static QColormap *qt_mac_global_map = 0;

void QColormap::initialize()
{
    qt_mac_global_map = new QColormap;
}

void QColormap::cleanup()
{
    delete qt_mac_global_map;
    qt_mac_global_map = 0;
}

QColormap QColormap::instance(int)
{
    return *qt_mac_global_map;
}

QColormap::QColormap() : d(new QColormapPrivate)
{ d->ref = 1; }

QColormap::QColormap(const QColormap &colormap) :d (colormap.d)
{ d->ref.ref(); }

QColormap::~QColormap()
{
    if (!d->ref.deref())
        delete d;
}

QColormap::Mode QColormap::mode() const
{ return QColormap::Direct; }

int QColormap::depth() const
{
    return 32;
}

int QColormap::size() const
{
    return -1;
}

uint QColormap::pixel(const QColor &color) const
{ return color.rgba(); }

const QColor QColormap::colorAt(uint pixel) const
{ return QColor(pixel); }

const QVector<QColor> QColormap::colormap() const
{ return QVector<QColor>(); }
