/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#include "guideline.h"
#include <cmath>

GuideLine::GuideLine(const QLineF &line, Guide *follows) : Guide(follows)
{
    this->line = line;
}

GuideLine::GuideLine(const QPointF &end, Guide *follows) : Guide(follows)
{
    if (follows)
        this->line = QLineF(prevGuide->endPos(), end);
    else
        this->line = QLineF(QPointF(0, 0), end);
}

float GuideLine::length()
{
    return line.length();
}

QPointF GuideLine::startPos()
{
    return QPointF(this->line.p1().x() * scaleX, this->line.p1().y() * scaleY);
}

QPointF GuideLine::endPos()
{
    return QPointF(this->line.p2().x() * scaleX, this->line.p2().y() * scaleY);
}

void GuideLine::guide(DemoItem *item, float moveSpeed)
{
    float frame = item->guideFrame - this->startLength;
    float endX = (this->line.p1().x() + (frame * this->line.dx() / this->length())) * scaleX;
    float endY = (this->line.p1().y() + (frame * this->line.dy() / this->length())) * scaleY;
    QPointF pos(endX, endY);
    this->move(item, pos, moveSpeed);
}

