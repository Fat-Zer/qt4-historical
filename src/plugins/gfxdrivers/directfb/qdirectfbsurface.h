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

#ifndef QDIRECFBWINDOWSURFACE_H
#define QDIRECFBWINDOWSURFACE_H

#include "qdirectfbpaintengine.h"

#include <private/qpaintengine_raster_p.h>
#include <private/qwindowsurface_qws_p.h>
#include <directfb.h>

class QDirectFBSurface :
    public QWSWindowSurface, public QCustomRasterPaintDevice
{
public:
    QDirectFBSurface();
    QDirectFBSurface(QWidget *widget);
    ~QDirectFBSurface();

    bool isValid() const;

    void setGeometry(const QRect &rect, const QRegion &mask);

    QString key() const { return QLatin1String("directfb"); }
    QByteArray permanentState() const;
    void setPermanentState(const QByteArray &state);

    bool scroll(const QRegion &area, int dx, int dy);

    bool move(const QPoint &offset);
    QRegion move(const QPoint &offset, const QRegion &newClip);

    QImage image() const { return QImage(); }
    QPaintDevice* paintDevice() { return this; }
    QPaintEngine* paintEngine() const;

    void flush(QWidget *widget, const QRegion &region, const QPoint &offset);

    IDirectFBSurface* surface() const { return dfbSurface; }

    void beginPaint(const QRegion &);
    void endPaint(const QRegion &);

    QImage* buffer(const QWidget *widget);
    void* memory() const;
    int bytesPerLine() const;

    bool lockDirectFB();
    void unlockDirectFB();

private:
#ifndef QT_NO_DIRECTFB_WM
    void createWindow();
    IDirectFBWindow *dfbWindow;
#endif
    IDirectFBSurface *dfbSurface;
    QDirectFBPaintEngine *engine;

    bool onscreen;

    QList<QImage*> bufferImages;
    QImage *surfaceImage;
};

#endif // QDIRECFBWINDOWSURFACE_H
