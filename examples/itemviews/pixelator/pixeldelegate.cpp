/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
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

#include <QtGui>

#include "pixeldelegate.h"

PixelDelegate::PixelDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{
    pixelSize = 12;
}

void PixelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);

    if (option.state & QStyle::State_Selected)
        painter->setBrush(option.palette.highlight());
    else
        painter->setBrush(QBrush(Qt::white));

    painter->drawRect(option.rect);

    if (option.state & QStyle::State_Selected)
        painter->setBrush(option.palette.highlightedText());
    else
        painter->setBrush(QBrush(Qt::black));

    int size = qMin(option.rect.width(), option.rect.height());
    int brightness = index.model()->data(index, Qt::DisplayRole).toInt();
    double radius = (size/2.0) - (brightness/255.0 * size/2.0);

    painter->drawEllipse(QRectF(option.rect.x() + option.rect.width()/2 - radius,
                                option.rect.y() + option.rect.height()/2 - radius,
                                2*radius, 2*radius));
}

QSize PixelDelegate::sizeHint(const QStyleOptionViewItem & /* option */,
                              const QModelIndex & /* index */) const
{
    return QSize(pixelSize, pixelSize);
}

void PixelDelegate::setPixelSize(int size)
{
    pixelSize = size;
}
