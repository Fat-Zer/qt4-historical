/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. 
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <private/qt_x11_p.h>

#include <limits.h>

QT_BEGIN_NAMESPACE

QRegion::QRegionData QRegion::shared_empty = {Q_BASIC_ATOMIC_INITIALIZER(1), 0, 0, 0};

void QRegion::updateX11Region() const
{
    d->rgn = XCreateRegion();
    if (!d->qt_rgn)
        return;

    int n = d->qt_rgn->numRects;
    const QRect *rect = (n == 1 ? &d->qt_rgn->extents : d->qt_rgn->rects.constData());
    while (n--) {
        XRectangle r;
        r.x = qMax(SHRT_MIN, rect->x());
        r.y = qMax(SHRT_MIN, rect->y());
        r.width = qMin((int)USHRT_MAX, rect->width());
        r.height = qMin((int)USHRT_MAX, rect->height());
        XUnionRectWithRegion(&r, d->rgn, d->rgn);
        ++rect;
    }
}

void *QRegion::clipRectangles(int &num) const
{
    if (!d->xrectangles && !(d == &shared_empty || d->qt_rgn->numRects == 0)) {
        XRectangle *r = static_cast<XRectangle*>(malloc(d->qt_rgn->numRects * sizeof(XRectangle)));
        d->xrectangles = r;
        int n = d->qt_rgn->numRects;
        const QRect *rect = (n == 1 ? &d->qt_rgn->extents : d->qt_rgn->rects.constData());
        while (n--) {
            r->x = qMax(SHRT_MIN, rect->x());
            r->y = qMax(SHRT_MIN, rect->y());
            r->width = qMin((int)USHRT_MAX, rect->width());
            r->height = qMin((int)USHRT_MAX, rect->height());
            ++r;
            ++rect;
        }
    }
    if (d == &shared_empty || d->qt_rgn->numRects == 0)
        num = 0;
    else
        num = d->qt_rgn->numRects;
    return d->xrectangles;
}

QT_END_NAMESPACE
