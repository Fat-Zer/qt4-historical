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

#ifndef QPIXMAPDATA_X11_P_H
#define QPIXMAPDATA_X11_P_H

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

#include "QtGui/qx11info_x11.h"

QT_BEGIN_NAMESPACE

class QX11PaintEngine;

class QX11PixmapData : public QPixmapData
{
public:
    QX11PixmapData(PixelType type);
//     QX11PixmapData(PixelType type, int width, int height);
//     QX11PixmapData(PixelType type, const QImage &image,
//                    Qt::ImageConversionFlags flags);
    ~QX11PixmapData();

    void resize(int width, int height);
    void fromImage(const QImage &image, Qt::ImageConversionFlags flags);
    void copy(const QPixmapData *data, const QRect &rect);

    void fill(const QColor &color);
    QBitmap mask() const;
    void setMask(const QBitmap &mask);
    bool hasAlphaChannel() const;
    void setAlphaChannel(const QPixmap &alphaChannel);
    QPixmap alphaChannel() const;
    QPixmap transformed(const QTransform &transform,
                        Qt::TransformationMode mode) const;
    QImage toImage() const;
    QPaintEngine* paintEngine() const;

    Qt::HANDLE handle() const { return hd; }
    Qt::HANDLE x11ConvertToDefaultDepth();

protected:
    int metric(QPaintDevice::PaintDeviceMetric metric) const;

private:
    friend class QPixmap;
    friend class QBitmap;
    friend class QX11PaintEngine;

    void release();

    QBitmap mask_to_bitmap(int screen) const;
    static Qt::HANDLE bitmap_to_mask(const QBitmap &, int screen);
    void bitmapFromImage(const QImage &image);

    Qt::HANDLE hd;

    int w, h;
    short d;
    uint uninit:1;

    QX11Info xinfo;
    Qt::HANDLE x11_mask;
    Qt::HANDLE picture;
    Qt::HANDLE mask_picture;
    Qt::HANDLE hd2; // sorted in the default display depth
#ifndef QT_NO_XRENDER
    void convertToARGB32();
#endif

    QX11PaintEngine *pengine;
};

QT_END_NAMESPACE

#endif // QPIXMAPDATA_X11_P_H

