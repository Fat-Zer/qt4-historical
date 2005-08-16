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

#ifndef SORTINGBOX_H
#define SORTINGBOX_H

#include <QWidget>

#include "shapeitem.h"

class QAction;
class QPoint;
class QToolButton;

class SortingBox : public QWidget
{
    Q_OBJECT

public:
    SortingBox();

protected:
    bool event(QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void createNewCircle();
    void createNewSquare();
    void createNewTriangle();

private:
    int updateButtonGeometry(QToolButton *button, int x, int y);
    void createShapeItem(const QPainterPath &path, const QString &toolTip,
                         const QPoint &pos, const QColor &color);
    int itemAt(const QPoint &pos);
    void moveItemTo(const QPoint &pos);
    QPoint initialItemPosition(const QPainterPath &path);
    QPoint randomItemPosition();
    QColor initialItemColor();
    QColor randomItemColor();
    QToolButton *createToolButton(const QString &toolTip, const QIcon &icon,
                                  const char *member);

    QList<ShapeItem> shapeItems;
    QPainterPath circlePath;
    QPainterPath squarePath;
    QPainterPath trianglePath;

    QPoint previousPosition;
    ShapeItem *itemInMotion;

    QToolButton *newCircleButton;
    QToolButton *newSquareButton;
    QToolButton *newTriangleButton;
};

#endif
