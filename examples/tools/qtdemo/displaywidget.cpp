/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
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

#include "displayshape.h"
#include "displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent)
    : QWidget(parent)
{
    empty = true;
    emptying = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateShapes()));
    timer->setSingleShot(false);
    enableUpdates();

    setBackgroundRole(QPalette::Base);
    setMouseTracking(true);
}

void DisplayWidget::appendShape(DisplayShape *shape)
{
    shapes.append(shape);
    empty = false;
    enableUpdates();
}

void DisplayWidget::insertShape(int position, DisplayShape *shape)
{
    shapes.insert(position, shape);
    empty = false;
    enableUpdates();
}

QSize DisplayWidget::minimumSizeHint() const
{
    return QSize(800, 600);
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (emptying)
        return;

    bool updated = false;

    foreach (DisplayShape *shape, shapes) {
        if (shape->isInteractive() && shape->rect().contains(event->pos())
            && !shape->contains("fade")) {
            shape->setMetaData("highlight", true);
            updated = true;
        } else if (shape->isInteractive() && shape->contains("highlight")) {
            shape->setMetaData("highlight", false);
            updated = true;
        }
    }

    if (updated)
        enableUpdates();
}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if (emptying)
        return;

    foreach (DisplayShape *shape, shapes) {
        if (shape->rect().contains(event->pos()) && !shape->contains("fade")) {
            if (shape->contains("action"))
                emit actionRequested(shape->metaData("action").toString());
            else if (shape->contains("category"))
                emit categoryRequested(shape->metaData("category").toString());
            else if (shape->contains("example"))
                emit exampleRequested(shape->metaData("example").toString());
            else if (shape->contains("documentation")) {
                emit documentationRequested(
                    shape->metaData("documentation").toString());
                shape->setMetaData("highlight", false);
                enableUpdates();
            } else if (shape->contains("launch")) {
                emit launchRequested(shape->metaData("launch").toString());
                shape->setMetaData("fade", -5);
                enableUpdates();
            }
        }
    }
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);
    foreach (DisplayShape *shape, shapes)
        shape->paint(&painter);
    painter.end();
}

void DisplayWidget::reset()
{
    if (emptying)
        return;

    if (shapes.size() == 0) {
        empty = true;
        timer->stop();
        emit displayEmpty();    // Note: synchronous signal
    } else {
        enableUpdates();
        emptying = true;
        empty = false;
        foreach (DisplayShape *shape, shapes) {
            shape->setMetaData("fade", -15);
            shape->setMetaData("fade minimum", 0);
        }
    }
}

DisplayShape *DisplayWidget::shape(int index) const
{
    return shapes.value(index);
}

int DisplayWidget::shapesCount() const
{
    return shapes.size();
}

void DisplayWidget::enableUpdates()
{
    if (!timer->isActive())
        timer->start(50);
}

void DisplayWidget::updateShapes()
{
    QVector<DisplayShape*> discard;

    int updated = 0;

    foreach (DisplayShape *shape, shapes) {
        QRect oldRect = shape->rect().toRect().adjusted(-1,-1,1,1);
        if (shape->animate()) {

            update(oldRect);
            QRect newRect = shape->rect().toRect().adjusted(-1,-1,1,1);
            ++updated;

            if (shape->contains("destroy")) {
                discard.append(shape);
            } else {
                update(newRect);
            }
        }
    }

    if (updated == 0)
        timer->stop();

    foreach (DisplayShape *shape, discard) {
        shapes.removeAll(shape);
        delete shape;
    }

    if (shapes.size() == 0 && !empty) {
        empty = true;
        emptying = false;
        timer->stop();
        emit displayEmpty();    // Note: synchronous signal
    }
}
