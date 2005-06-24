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

#include "shapeitem.h"

QPainterPath ShapeItem::path() const
{
    return myPath;
}

QPoint ShapeItem::position() const
{
    return myPosition;
}

QColor ShapeItem::color() const
{
    return myColor;
}

QString ShapeItem::toolTip() const
{
    return myToolTip;
}

void ShapeItem::setPath(const QPainterPath &path)
{
    myPath = path;
}

void ShapeItem::setToolTip(const QString &toolTip)
{
    myToolTip = toolTip;
}

void ShapeItem::setPosition(const QPoint &position)
{
    myPosition = position;
}

void ShapeItem::setColor(const QColor &color)
{
    myColor = color;
}
