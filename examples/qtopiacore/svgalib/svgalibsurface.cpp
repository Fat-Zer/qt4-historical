/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#include "svgalibsurface.h"
#include "svgalibpaintdevice.h"

#include <vgagl.h>

SvgalibSurface::SvgalibSurface() : QWSWindowSurface(), pdevice(0)
{
    setSurfaceFlags(Opaque);
}

SvgalibSurface::SvgalibSurface(QWidget *w)
    : QWSWindowSurface(w)
{
    setSurfaceFlags(Opaque);
    pdevice = new SvgalibPaintDevice(w);
}

SvgalibSurface::~SvgalibSurface()
{
    delete pdevice;
}

void SvgalibSurface::setGeometry(const QRect &rect)
{
    QWSWindowSurface::setGeometry(rect);
}

QPoint SvgalibSurface::painterOffset() const
{
    return geometry().topLeft() + QWSWindowSurface::painterOffset();
}

bool SvgalibSurface::scroll(const QRegion &region, int dx, int dy)
{
    const QVector<QRect> rects = region.rects();
    for (int i = 0; i < rects.size(); ++i) {
        const QRect r = rects.at(i);
        gl_copybox(r.left(), r.top(), r.width(), r.height(),
                   r.left() + dx, r.top() + dy);
    }

    return true;
}

