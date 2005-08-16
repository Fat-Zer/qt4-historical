/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include "qatomic.h"
#include "qbitmap.h"
#include "qbuffer.h"
#include "qimage.h"
#include "qpolygon.h"
#include "qregion.h"
#include "qt_windows.h"
#include "qguifunctions_wince.h"
#include "qpainterpath.h"

QT_BEGIN_NAMESPACE

QRegion::QRegionData QRegion::shared_empty = { Q_BASIC_ATOMIC_INITIALIZER(1), 0, 0 };

HRGN qt_tryCreateRegion(QRegion::RegionType type, int left, int top, int right, int bottom)
{
    const int tries = 10;
    for (int i = 0; i < tries; ++i) {
        HRGN region;
        switch (type) {
        case QRegion::Rectangle:
            region = CreateRectRgn(left, top, right, bottom);
            break;
        case QRegion::Ellipse:
#ifndef Q_OS_WINCE
            region = CreateEllipticRgn(left, top, right, bottom);
#endif
            break;
        }
        if (region) {
            if (GetRegionData(region, 0, 0))
                return region;
            else
                DeleteObject(region);
        }
    }
    return 0;
}

void qt_win_dispose_rgn(HRGN r)
{
    if (r)
        DeleteObject(r);
}

static void qt_add_rect(HRGN &winRegion, QRect r)
{
    HRGN rgn = CreateRectRgn(r.left(), r.top(), r.x() + r.width(), r.y() + r.height());
    if (rgn) {
        HRGN dest = CreateRectRgn(0,0,0,0);
        int result = CombineRgn(dest, winRegion, rgn, RGN_OR);
        if (result) {
            DeleteObject(winRegion);
            winRegion = dest;
        }
    }
}

void QRegion::ensureHandle() const
{
    if (d->rgn)
        DeleteObject(d->rgn);
    d->rgn = CreateRectRgn(0,0,0,0);
    if (d->qt_rgn) {
        if (d->qt_rgn->numRects == 1) {
            QRect r = d->qt_rgn->extents;
            qt_add_rect(d->rgn, r);
            return;
        }
        for (int i = 0;i < d->qt_rgn->numRects;i++) {
            QRect r = d->qt_rgn->rects.at(i);
            qt_add_rect(d->rgn, r);
        }
    }
}


QT_END_NAMESPACE
