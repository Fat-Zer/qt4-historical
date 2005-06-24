/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>

#include "draglabel.h"

DragLabel::DragLabel(const QString &text, QWidget *parent)
    : QLabel(parent)
{
    QFontMetrics fm(font());
    QSize size = fm.size(Qt::TextSingleLine, text);

    QImage image(size.width() + 12, size.height() + 12, QImage::Format_ARGB32_Premultiplied);
    image.fill(qRgba(0, 0, 0, 0));

    QFont font;
    font.setStyleStrategy(QFont::ForceOutline);

    QPainter painter;
    painter.begin(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    painter.drawRoundRect(QRectF(0.5, 0.5, image.width()-1, image.height()-1), 25, 25);

    painter.setFont(font);
    painter.setBrush(Qt::black);
    painter.drawText(QRect(QPoint(6, 6), size), Qt::AlignCenter, text);
    painter.end();

    setPixmap(QPixmap::fromImage(image));
    labelText = text;
}

void DragLabel::mousePressEvent(QMouseEvent *event)
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << labelText << QPoint(event->pos() - rect().topLeft());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-fridgemagnet", itemData);
    mimeData->setText(labelText);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - rect().topLeft());
    drag->setPixmap(*pixmap());

    hide();

    if (drag->start(Qt::MoveAction) == Qt::MoveAction)
        close();
    else
        show();
}
