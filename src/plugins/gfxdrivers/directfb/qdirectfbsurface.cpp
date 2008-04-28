/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the plugins of the Qt Toolkit.
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

#include "qdirectfbsurface.h"
#include "qdirectfbscreen.h"
#include "qdirectfbpaintengine.h"

#include <qwidget.h>
#include <qpaintdevice.h>
#include <qvarlengtharray.h>

QDirectFBSurface::QDirectFBSurface()
    : QCustomRasterPaintDevice(0)
#ifndef QT_NO_DIRECTFB_WM
    , dfbWindow(0)
#endif
    , dfbSurface(0), engine(new QDirectFBPaintEngine), mem(0), bpl(0)
{
    setSurfaceFlags(Opaque | Buffered);
}

QDirectFBSurface::QDirectFBSurface(QWidget *widget)
    : QWSWindowSurface(widget), QCustomRasterPaintDevice(widget)
#ifndef QT_NO_DIRECTFB_WM
    , dfbWindow(0)
#endif
    , dfbSurface(0), engine(new QDirectFBPaintEngine), mem(0), bpl(0)
{
    onscreen = widget->testAttribute(Qt::WA_PaintOnScreen);
    if (onscreen)
        setSurfaceFlags(Opaque | RegionReserved);
    else
        setSurfaceFlags(Opaque | Buffered);
}

QDirectFBSurface::~QDirectFBSurface()
{
}

bool QDirectFBSurface::isValid() const
{
    return true;
}

#ifndef QT_NO_DIRECTFB_WM
void QDirectFBSurface::createWindow()
{
    IDirectFBDisplayLayer *layer = QDirectFBScreen::instance()->dfbDisplayLayer();
    if (!layer)
        qFatal("QDirectFBWindowSurface: Unable to get primary display layer!");

    DFBWindowDescription  description;
    description.caps = DFBWindowCapabilities(DWCAPS_NODECORATION |
                                             DWCAPS_ALPHACHANNEL);
    description.flags = DWDESC_CAPS;

    DFBResult result = layer->CreateWindow(layer, &description, &dfbWindow);
    if (result != DFB_OK)
        DirectFBErrorFatal("QDirectFBWindowSurface::createWindow", result);

    dfbWindow->GetSurface(dfbWindow, &dfbSurface);
}
#endif // QT_NO_DIRECTFB_WM

void QDirectFBSurface::setGeometry(const QRect &rect, const QRegion &mask)
{
    if (rect.isNull()) {
#ifndef QT_NO_DIRECTFB_WM
        if (dfbWindow) {
            dfbWindow->Destroy(dfbWindow);
            dfbWindow = 0;
        }
#endif
        if (dfbSurface) {
            dfbSurface->Release(dfbSurface);
            dfbSurface = 0;
        }
    } else if (rect != geometry()) {
        const bool isResize = rect.size() != geometry().size();
        DFBResult result = DFB_OK;

        IDirectFBSurface *s = QDirectFBScreen::instance()->dfbSurface();
        if (onscreen && s) {
            if (dfbSurface)
                dfbSurface->Release(dfbSurface);

            DFBRectangle r = { rect.x(), rect.y(),
                               rect.width(), rect.height() };
            result = s->GetSubSurface(s, &r, &dfbSurface);
        } else {
#ifndef QT_NO_DIRECTFB_WM
            const bool isMove = rect.topLeft() != geometry().topLeft();

            if (!dfbWindow)
                createWindow();

            if (isResize && isMove)
                result = dfbWindow->SetBounds(dfbWindow, rect.x(), rect.y(),
                                              rect.width(), rect.height());
            else if (isResize)
                result = dfbWindow->Resize(dfbWindow,
                                           rect.width(), rect.height());
            else if (isMove)
                result = dfbWindow->MoveTo(dfbWindow, rect.x(), rect.y());
#else
            if (isResize) {
                if (dfbSurface)
                    dfbSurface->Release(dfbSurface);

                IDirectFB *dfb = QDirectFBScreen::instance()->dfb();
                if (!dfb) {
                    qFatal("QDirectFBWindowSurface::setGeometry(): "
                           "Unable to get DirectFB handle!");
                }

                DFBSurfaceDescription description;
                description.flags = DFBSurfaceDescriptionFlags(DSDESC_WIDTH |
                                                               DSDESC_HEIGHT |
                                                               DSDESC_CAPS |
                                                               DSDESC_PIXELFORMAT);
                description.width = rect.width();
                description.height = rect.height();
                description.pixelformat = DSPF_ARGB;
                description.caps = DSCAPS_VIDEOONLY;

                result = dfb->CreateSurface(dfb, &description, &dfbSurface);
            } else {
                Q_ASSERT(dfbSurface);
            }
#endif
        }

        if (result != DFB_OK)
            DirectFBErrorFatal("QDirectFBSurface::setGeometry()", result);
    }

    QWSWindowSurface::setGeometry(rect, mask);
}

QByteArray QDirectFBSurface::permanentState() const
{
    QByteArray array;
#ifdef QT_NO_DIRECTFB_WM
    array.resize(sizeof(SurfaceFlags) + sizeof(IDirectFBSurface*));
#else
    array.resize(sizeof(SurfaceFlags));
#endif
    char *ptr = array.data();

    *reinterpret_cast<SurfaceFlags*>(ptr) = surfaceFlags();
    ptr += sizeof(SurfaceFlags);

#ifdef QT_NO_DIRECTFB_WM
    *reinterpret_cast<IDirectFBSurface**>(ptr) = dfbSurface;
#endif
    return array;
}

void QDirectFBSurface::setPermanentState(const QByteArray &state)
{
    SurfaceFlags flags;
    const char *ptr = state.constData();

    flags = *reinterpret_cast<const SurfaceFlags*>(ptr);
    setSurfaceFlags(flags);

#ifdef QT_NO_DIRECTFB_WM
    ptr += sizeof(SurfaceFlags);
    dfbSurface = *reinterpret_cast<IDirectFBSurface* const*>(ptr);
#endif
}

bool QDirectFBSurface::scroll(const QRegion &region, int dx, int dy)
{
    if (!dfbSurface)
        return false;

    const QVector<QRect> rects = region.rects();
    const int n = rects.size();

    QVarLengthArray<DFBRectangle, 8> dfbRects(n);
    QVarLengthArray<DFBPoint, 8> dfbPoints(n);

    for (int i = 0; i < n; ++i) {
        const QRect r = rects.at(i);
        dfbRects[i].x = r.x();
        dfbRects[i].y = r.y();
        dfbRects[i].w = r.width();
        dfbRects[i].h = r.height();
        dfbPoints[i].x = r.x() + dx;
        dfbPoints[i].y = r.y() + dy;
    }

    dfbSurface->SetBlittingFlags(dfbSurface, DSBLIT_NOFX);
    dfbSurface->BatchBlit(dfbSurface, dfbSurface,
                          dfbRects.data(), dfbPoints.data(), n);

    return true;
}

bool QDirectFBSurface::move(const QPoint &offset)
{
    QWSWindowSurface::move(offset);

#ifdef QT_NO_DIRECTFB_WM
    return true; // buffered
#else
    if (!dfbWindow)
        return false;

    DFBResult status = dfbWindow->Move(dfbWindow, offset.x(), offset.y());
    return (status == DFB_OK);
#endif
}

QRegion QDirectFBSurface::move(const QPoint &offset, const QRegion &newClip)
{
#ifdef QT_NO_DIRECTFB_WM
    return QWSWindowSurface::move(offset, newClip);
#else
    Q_UNUSED(offset);
    Q_UNUSED(newClip);

    // DirectFB handles the entire move, so there's no need to blit.
    return QRegion();
#endif
}

QPaintEngine* QDirectFBSurface::paintEngine() const
{
    return engine;
}

void QDirectFBSurface::flush(QWidget *widget, const QRegion &region,
                             const QPoint &offset)
{
#ifndef QT_NO_DIRECTFB_WM
    const quint8 winOpacity = quint8(window()->windowOpacity() * 255);
    quint8 opacity;

    dfbWindow->GetOpacity(dfbWindow, &opacity);
    if (winOpacity != opacity)
        dfbWindow->SetOpacity(dfbWindow, winOpacity);
#endif

    // XXX: have to call the base function first as the decoration is
    // currently painted there
    QWSWindowSurface::flush(widget, region, offset);

#ifndef QT_NO_DIRECTFB_WM
    const QRect br = region.boundingRect().translated(painterOffset());
    DFBRegion r = { br.topLeft().x(), br.topLeft().y(),
                    br.bottomRight().x(), br.bottomRight().y() };

    dfbSurface->Flip(dfbSurface, &r, DSFLIP_NONE);
#endif
}

void QDirectFBSurface::beginPaint(const QRegion &)
{
    DFBResult result = dfbSurface->Lock(dfbSurface, DSLF_WRITE, &mem, &bpl);
    if (result != DFB_OK)
        DirectFBError("QDirectFBSurface::beginPaint()", result);
    dfbSurface->Unlock(dfbSurface); // trick to get to the framebuffer without locking
}

void QDirectFBSurface::endPaint(const QRegion &)
{
    qDeleteAll(bufferImages);
    mem = 0;
    bpl = 0;
}


QImage* QDirectFBSurface::buffer(const QWidget *widget)
{
    if (!mem)
        return 0;

    const QPoint off = offset(widget);
    QRect rect(off, widget->size());
    rect &= QRect(QPoint(), geometry().size());

    if (rect.isEmpty())
        return 0;

    QImage *img = new QImage(static_cast<uchar*>(mem)
                             + rect.y() * bpl + rect.x() * 4,
                             rect.width(), rect.height(),
                             bpl, QImage::Format_ARGB32_Premultiplied);
    bufferImages.append(img);

    return img;
}

