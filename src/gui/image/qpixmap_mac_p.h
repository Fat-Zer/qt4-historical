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
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
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

#ifndef QPIXMAP_MAC_P_H
#define QPIXMAP_MAC_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/private/qpixmapdata_p.h>
#include <QtGui/private/qpixmapdatafactory_p.h>

QT_BEGIN_NAMESPACE

class QMacPixmapData : public QPixmapData
{
public:
    QMacPixmapData(PixelType type);
    ~QMacPixmapData();

    void resize(int width, int height);
    void fromImage(const QImage &image, Qt::ImageConversionFlags flags);
    void copy(const QPixmapData *data, const QRect &rect);

    int metric(QPaintDevice::PaintDeviceMetric metric) const;
    void fill(const QColor &color);
    QBitmap mask() const;
    void setMask(const QBitmap &mask);
    bool hasAlphaChannel() const;
//     QPixmap transformed(const QTransform &matrix,
//                         Qt::TransformationMode mode) const;
    void setAlphaChannel(const QPixmap &alphaChannel);
    QPixmap alphaChannel() const;
    QImage toImage() const;
    QPaintEngine* paintEngine() const;

private:
    int w, h, d;

    uint has_alpha : 1, has_mask : 1, uninit : 1;

    void macSetHasAlpha(bool b);
    void macGetAlphaChannel(QMacPixmapData *, bool asMask) const;
    void macSetAlphaChannel(const QMacPixmapData *, bool asMask);
    void macCreateCGImageRef();
    void macCreatePixels();
    void macReleaseCGImageRef();
    /*
        pixels stores the pixmap data. pixelsToFree is either 0 or some memory
        block that was bound to a CGImageRef and released, and for which the
        release callback has been called. There are two uses to pixelsToFree:

        1. If pixels == pixelsToFree, then we know that the CGImageRef is done\
           with the data and we can modify pixels without breaking CGImageRef's
           mutability invariant.

        2. If pixels != pixelsToFree and pixelsToFree != 0, then we can reuse
           pixelsToFree later on instead of malloc'ing memory.
    */
    quint32 *pixels;
    quint32 *pixelsToFree;
    uint bytesPerRow;
    QRectF cg_mask_rect;
    CGImageRef cg_data, cg_dataBeingReleased, cg_mask;
#ifndef QT_MAC_NO_QUICKDRAW
    GWorldPtr qd_data, qd_alpha;
    void macQDDisposeAlpha();
    void macQDUpdateAlpha();
#endif

    QPaintEngine *pengine;

    friend class QPixmap;
    friend class QRasterBuffer;
    friend class QRasterPaintEngine;
    friend class QCoreGraphicsPaintEngine;
    friend QPixmap qt_mac_unmultiplyPixmapAlpha(const QPixmap&);
    friend CGImageRef qt_mac_create_imagemask(const QPixmap&, const QRectF&);
    friend quint32 *qt_mac_pixmap_get_base(const QPixmap*);
    friend int qt_mac_pixmap_get_bytes_per_line(const QPixmap*);
    friend void qt_mac_cgimage_data_free(void *, const void*, size_t);
    friend IconRef qt_mac_create_iconref(const QPixmap&);
    friend CGContextRef qt_mac_cg_context(const QPaintDevice*);
};

QT_END_NAMESPACE

#endif // QPIXMAP_MAC_P_H
