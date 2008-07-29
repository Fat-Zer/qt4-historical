 /****************************************************************************
 **
 ** Copyright (C) 2005-2008 Trolltech ASA. All rights reserved.
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

#include "dbscreen.h"
#include <QApplication>

//! [0]
bool DBScreen::initDevice()
{
    if (!QLinuxFbScreen::initDevice())
        return false;

    QScreenCursor::initSoftwareCursor();
    image = new QImage(deviceWidth(), deviceHeight(), pixelFormat());
    painter = new QPainter(image);

    return true;
}
//! [0]

//! [1]
void DBScreen::shutdownDevice()
{
    QLinuxFbScreen::shutdownDevice();
    delete painter;
    delete image;
}
//! [1]

//! [2]
void DBScreen::solidFill(const QColor &color, const QRegion &region)
{
    QVector<QRect> rects = region.rects();
    for (int i = 0; i  < rects.size(); i++)
        painter->fillRect(rects.at(i), color);
}
//! [2]

//! [3]
void DBScreen::blit(const QImage &image, const QPoint &topLeft, const QRegion &region)
{
    QVector<QRect> rects = region.rects();
    for (int i = 0; i < rects.size(); i++) {
        QRect destRect = rects.at(i);
        QRect srcRect(destRect.x()-topLeft.x(), destRect.y()-topLeft.y(), destRect.width(), destRect.height());
        painter->drawImage(destRect.topLeft(), image, srcRect);
    }
}
//! [3]

//! [4]
void DBScreen::exposeRegion(QRegion region, int changing)
{
    QLinuxFbScreen::exposeRegion(region, changing);
    QLinuxFbScreen::blit(*image, QPoint(0, 0), region);
}
//! [4]

