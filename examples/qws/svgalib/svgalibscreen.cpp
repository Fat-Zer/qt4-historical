/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#include "svgalibscreen.h"
#include "svgalibsurface.h"

#include <QVector>
#include <QApplication>
#include <QColor>
#include <QWidget>

#include <math.h>

static int getModeDepth(vga_modeinfo *mode)
{
    const int bits = int(log2(mode->colors));
    if (bits == 24 && mode->bytesperpixel == 4)
        return 32;
    return bits;
}

//! [0]
bool SvgalibScreen::connect(const QString &displaySpec)
{
    int mode = vga_getdefaultmode();
    if (mode <= 0) {
        qCritical("SvgalibScreen::connect(): invalid vga mode");
        return false;
    }

    vga_modeinfo *modeinfo = vga_getmodeinfo(mode);

    QScreen::lstep = modeinfo->linewidth;
    QScreen::dw = QScreen::w = modeinfo->width;
    QScreen::dh = QScreen::h = modeinfo->height;
    QScreen::d = getModeDepth(modeinfo);
    QScreen::size = QScreen::lstep * dh;
    QScreen::data = 0;

    switch (depth()) {
    case 32:
        setPixelFormat(QImage::Format_ARGB32_Premultiplied);
        break;
    case 24:
        setPixelFormat(QImage::Format_RGB888);
        break;
    case 16:
        setPixelFormat(QImage::Format_RGB16);
        break;
    case 15:
        setPixelFormat(QImage::Format_RGB555);
        break;
    default:
        break;
    }

    const int dpi = 72;
    QScreen::physWidth = qRound(QScreen::dw * 25.4 / dpi);
    QScreen::physHeight = qRound(QScreen::dh * 25.4 / dpi);

    const QStringList args = displaySpec.split(QLatin1Char(':'),
                                               QString::SkipEmptyParts);
    grayscale = args.contains(QLatin1String("grayscale"), Qt::CaseInsensitive);

    return true;
}
//! [0]

void SvgalibScreen::initColorMap()
{
    const int numColors = vga_getcolors();
    if (numColors == 2 || numColors > 256) {
        screencols = 0;
        return; // not a palette based mode
    }

    if (numColors == 16) {
        if (grayscale) {
            for (int i = 0; i < 256; ++i) {
                const int c = i * 16 / 256;
                vga_setpalette(i, c, c, c);
            }
            screencols = 256; // XXX: takes advantage of optimization in alloc()
        } else { // read in EGA palette
            int r, g, b;
            for (int i = 0; i < 16; ++i) {
                vga_getpalette(i, &r, &g, &b);
                screenclut[i] = qRgb(r, g, b);
            }
            screencols = 16;
        }

        return;
    }

    Q_ASSERT(numColors == 256);

    if (grayscale) {
        for (int i = 0; i < 256; ++i) {
            const int c = i * 64 / 256;
            vga_setpalette(i, c, c, c);
        }
    } else {
        int i = 0;

#if 0
        // read in EGA palette
        while (i < 16) {
            int r, g, b;
            vga_getpalette(i, &r, &g, &b);
            screenclut[i] = qRgb(r, g, b);
            ++i;
        }
        screencols = 16;
#endif

        // 6 * 6 * 6 color cube
        for (int r = 0; r < 6; ++r) {
            for (int g = 0; g < 6; ++g) {
                for (int b = 0; b < 6; ++b) {
                    vga_setpalette(i, r * 64/6, g * 64/6, b * 64/6);
                    screenclut[i] = qRgb(r * 256/6, g * 256/6, b * 256/6);
                    ++i;
                }
            }
        }
        screencols = i;

        while (i < 256) {
            screenclut[i] = qRgb(0, 0, 0);
            ++i;
        }
    }
}

//! [1]
bool SvgalibScreen::initDevice()
{
    if (vga_init() != 0) {
        qCritical("SvgalibScreen::initDevice(): unable to initialize svgalib");
        return false;
    }

    int mode = vga_getdefaultmode();
    if (vga_setmode(mode) == -1) {
        qCritical("SvgalibScreen::initialize(): unable to set graphics mode");
        return false;
    }

    if (gl_setcontextvga(mode) != 0) {
        qCritical("SvgalibScreen::initDevice(): unable to set vga context");
        return false;
    }
    context = gl_allocatecontext();
    gl_getcontext(context);

    vga_modeinfo *modeinfo = vga_getmodeinfo(mode);
    if (modeinfo->flags & IS_LINEAR)
        QScreen::data = vga_getgraphmem();

    initColorMap();

    QScreenCursor::initSoftwareCursor();
    return true;
}
//! [1]

//! [2]
void SvgalibScreen::shutdownDevice()
{
    gl_freecontext(context);
    vga_setmode(TEXT);
}
//! [2]

//! [3]
void SvgalibScreen::disconnect()
{
}
//! [3]

//! [4]
void SvgalibScreen::solidFill(const QColor &color, const QRegion &reg)
{
    int c;
    if (depth() == 4 || depth() == 8)
        c = alloc(color.red(), color.green(), color.blue());
    else
        c = gl_rgbcolor(color.red(), color.green(), color.blue());

    const QVector<QRect> rects = (reg & region()).rects();
    for (int i = 0; i < rects.size(); ++i) {
        const QRect r = rects.at(i);
        gl_fillbox(r.left(), r.top(), r.width(), r.height(), c);
    }
}
//! [4]

void SvgalibScreen::blit16To8(const QImage &image,
                              const QPoint &topLeft, const QRegion &region)
{
    const int imageStride = image.bytesPerLine() / 2;
    const QVector<QRect> rects = region.rects();

    for (int i = 0; i < rects.size(); ++i) {
        const QRect r = rects.at(i).translated(-topLeft);
        int y = r.y();
        const quint16 *s = reinterpret_cast<const quint16*>(image.scanLine(y));

        while (y <= r.bottom()) {
            int x1 = r.x();
            while (x1 <= r.right()) {
                const quint16 c = s[x1];
                int x2 = x1;
                // find span length
                while ((x2+1 < r.right()) && (s[x2+1] == c))
                    ++x2;
                gl_hline(x1 + topLeft.x(), y + topLeft.y(), x2 + topLeft.x(),
                         qt_colorConvert<quint8, quint16>(c, 0));
                x1 = x2 + 1;
            }
            s += imageStride;
            ++y;
        }
    }
}

void SvgalibScreen::blit32To8(const QImage &image,
                              const QPoint &topLeft, const QRegion &region)
{
    const int imageStride = image.bytesPerLine() / 2;
    const QVector<QRect> rects = region.rects();

    for (int i = 0; i < rects.size(); ++i) {
        const QRect r = rects.at(i).translated(-topLeft);
        int y = r.y();
        const quint32 *s = reinterpret_cast<const quint32*>(image.scanLine(y));

        while (y <= r.bottom()) {
            int x1 = r.x();
            while (x1 <= r.right()) {
                const quint32 c = s[x1];
                int x2 = x1;
                // find span length
                while ((x2+1 < r.right()) && (s[x2+1] == c))
                    ++x2;
                gl_hline(x1 + topLeft.x(), y + topLeft.y(), x2 + topLeft.x(),
                         qt_colorConvert<quint8, quint32>(c, 0));
                x1 = x2 + 1;
            }
            s += imageStride;
            ++y;
        }
    }
}

//! [5]
void SvgalibScreen::blit(const QImage &img, const QPoint &topLeft,
                         const QRegion &reg)
{
    if (depth() == 8) {
        switch (img.format()) {
        case QImage::Format_RGB16:
            blit16To8(img, topLeft, reg);
            return;
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
            blit32To8(img, topLeft, reg);
            return;
        default:
            break;
        }
    }

    if (img.format() != pixelFormat()) {
        if (base())
            QScreen::blit(img, topLeft, reg);
        return;
    }

    const QVector<QRect> rects = (reg & region()).rects();

    for (int i = 0; i < rects.size(); ++i) {
        const QRect r = rects.at(i);
        gl_putboxpart(r.x(), r.y(), r.width(), r.height(),
                      img.width(), img.height(),
                      static_cast<void*>(const_cast<uchar*>(img.bits())),
                      r.x() - topLeft.x(), r.y() - topLeft.y());
    }
}
//! [5]

//! [7]
QWSWindowSurface* SvgalibScreen::createSurface(QWidget *widget) const
{
    if (base()) {
        static int onScreenPaint = -1;
        if (onScreenPaint == -1)
            onScreenPaint = qgetenv("QT_ONSCREEN_PAINT").toInt();

        if (onScreenPaint > 0 || widget->testAttribute(Qt::WA_PaintOnScreen))
            return new SvgalibSurface(widget);
    }
    return QScreen::createSurface(widget);
}
//! [7]

//! [8]
QWSWindowSurface* SvgalibScreen::createSurface(const QString &key) const
{
    if (key == QLatin1String("svgalib"))
        return new SvgalibSurface;
    return QScreen::createSurface(key);
}
//! [8]
