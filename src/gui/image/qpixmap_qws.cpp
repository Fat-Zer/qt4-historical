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

#include <qpixmap.h>
#include <qapplication.h>
#include <qwidget.h>
#include <qdesktopwidget.h>
#include <qscreen_qws.h>
#include <qwsdisplay_qws.h>
#include <private/qdrawhelper_p.h>
#include <private/qpixmap_raster_p.h>

QPixmap QPixmap::grabWindow(WId window, int x, int y, int w, int h)
{
    QWidget *widget = QWidget::find(window);
    if (!widget)
        return QPixmap();

    QRect grabRect = widget->frameGeometry();
    if (w < 0)
        w = widget->width() - x;
    if (h < 0)
        h = widget->height() - y;
    grabRect &= QRect(x, y, w, h).translated(widget->mapToGlobal(QPoint()));

    QScreen *screen = qt_screen;
    QDesktopWidget *desktop = QApplication::desktop();
    if (!desktop)
        return QPixmap();
    if (desktop->numScreens() > 1) {
        const int screenNo = desktop->screenNumber(widget);
        if (screenNo != -1)
            screen = qt_screen->subScreens().at(screenNo);
        grabRect = grabRect.translated(-screen->region().boundingRect().topLeft());
    }

    if (screen->pixelFormat() == QImage::Format_Invalid) {
        qWarning("QPixmap::grabWindow(): Unable to copy pixels from framebuffer");
        return QPixmap();
    }

    if (screen->isTransformed()) {
        const QSize screenSize(screen->width(), screen->height());
        grabRect = screen->mapToDevice(grabRect, screenSize);
    }

    QWSDisplay::grab(false);
    QPixmap pixmap;
    QImage img(screen->base(),
               screen->deviceWidth(), screen->deviceHeight(),
               screen->linestep(), screen->pixelFormat());
    img = img.copy(grabRect);
    QWSDisplay::ungrab();

    if (screen->isTransformed()) {
        QMatrix matrix;
        switch (screen->transformOrientation()) {
        case 1: matrix.rotate(90); break;
        case 2: matrix.rotate(180); break;
        case 3: matrix.rotate(270); break;
        default: break;
        }
        img = img.transformed(matrix);
    }

    if (screen->pixelType() == QScreen::BGRPixel)
        img = img.rgbSwapped();

    return QPixmap::fromImage(img);
}

/*!
    \internal
*/
QRgb* QPixmap::clut() const
{
    if (data->classId() == QPixmapData::RasterClass) {
        const QRasterPixmapData *d = static_cast<const QRasterPixmapData*>(data);
        return d->image.colorTable().data();
    }

    return 0;
}

/*!
    \internal
*/
int QPixmap::numCols() const
{
    if (data->classId() == QPixmapData::RasterClass) {
        const QRasterPixmapData *d = static_cast<const QRasterPixmapData*>(data);
        return d->image.numColors();
    }

    return 0;
}

/*!
    \internal
    \since 4.1
*/
const uchar* QPixmap::qwsBits() const
{
    if (data->classId() == QPixmapData::RasterClass) {
        const QRasterPixmapData *d = static_cast<const QRasterPixmapData*>(data);
        return d->image.bits();
    }

    return 0;
}

/*!
    \internal
    \since 4.1
*/
int QPixmap::qwsBytesPerLine() const
{
    if (data->classId() == QPixmapData::RasterClass) {
        const QRasterPixmapData *d = static_cast<const QRasterPixmapData*>(data);
        return d->image.bytesPerLine();
    }

    return 0;
}
