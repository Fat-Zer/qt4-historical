/****************************************************************************
**
** Copyright (C) 2007-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
** 
** Trolltech ASA (c) 2007
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>

#include "diagramtextitem.h"
#include "diagramscene.h"

DiagramTextItem::DiagramTextItem(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsTextItem(parent, scene)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QVariant DiagramTextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
        emit selectedChange(this);
    return value;
}

void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void DiagramTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    scene()->clearSelection();
    QGraphicsTextItem::mousePressEvent(event);
    setSelected(true);
}

void DiagramTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() & Qt::TextEditable) {
        QGraphicsTextItem::mouseMoveEvent(event);
    } else
        QGraphicsItem::mouseMoveEvent(event);
}

void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsSceneMouseEvent *mouseEvent =
        new QGraphicsSceneMouseEvent(QEvent::GraphicsSceneMousePress);
    mouseEvent->setAccepted(true);
    mouseEvent->setPos(event->pos());
    mouseEvent->setScenePos(event->scenePos());
    mouseEvent->setScreenPos(event->screenPos());
    mouseEvent->setButtonDownPos(Qt::LeftButton,
        event->buttonDownPos(Qt::LeftButton));
    mouseEvent->setButtonDownScreenPos(Qt::LeftButton,
        event->buttonDownScreenPos(Qt::LeftButton));
    mouseEvent->setButtonDownScenePos(Qt::LeftButton,
        event->buttonDownScenePos(Qt::LeftButton));
    mouseEvent->setWidget(event->widget());

    QGraphicsTextItem::mousePressEvent(mouseEvent);

    delete mouseEvent;
}
