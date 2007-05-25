/****************************************************************************
**
** Copyright (C) 2006-2007 Trolltech ASA. All rights reserved.
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

#include "imageitem.h"

ImageItem::ImageItem(int id, const QPixmap &pixmap, QGraphicsItem *parent,
                     QGraphicsScene *scene)
    : QGraphicsPixmapItem(pixmap, parent, scene)
{
    recordId = id;
    setAcceptsHoverEvents(true);

    timeLine.setDuration(150);
    timeLine.setFrameRange(0, 150);

    connect(&timeLine, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
    connect(&timeLine, SIGNAL(finished()), this, SLOT(updateItemPosition()));

    adjust();
}

void ImageItem::hoverEnterEvent(QGraphicsSceneHoverEvent * /*event*/)
{
    timeLine.setDirection(QTimeLine::Forward);

    if (z != 1.0) {
        z = 1.0;
        updateItemPosition();
    }

    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}

void ImageItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * /*event*/)
{
    timeLine.setDirection(QTimeLine::Backward);
    if (z != 0.0)
        z = 0.0;

    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}

void ImageItem::setFrame(int frame)
{
    adjust();
    QPointF center = boundingRect().center();

    translate(center.x(), center.y());
    scale(1 + frame / 330.0, 1 + frame / 330.0);
    translate(-center.x(), -center.y());
}

void ImageItem::adjust()
{
    QMatrix matrix;
    matrix.scale(150/ boundingRect().width(), 120/ boundingRect().height());
    setMatrix(matrix);
}

int ImageItem::id()
{
    return recordId;
}

void ImageItem::updateItemPosition()
{
    setZValue(z);
}


