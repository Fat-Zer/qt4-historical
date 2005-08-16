/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

/****************************************************************
**
** Implementation CannonField class, Qt tutorial 8
**
****************************************************************/

#include <QPainter>

#include "cannonfield.h"

CannonField::CannonField(QWidget *parent)
    : QWidget(parent)
{
    currentAngle = 45;
    setPalette(QPalette(QColor(250, 250, 200)));
}

void CannonField::setAngle(int angle)
{
    if (angle < 5)
        angle = 5;
    if (angle > 70)
        angle = 70;
    if (currentAngle == angle)
        return;
    currentAngle = angle;
    update();
    emit angleChanged(currentAngle);
}

void CannonField::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.drawText(200, 200, "Angle = " + QString::number(currentAngle));
}
