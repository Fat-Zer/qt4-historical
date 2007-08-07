/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
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

#include <QPainter>

#include "cannonfield.h"

CannonField::CannonField(QWidget *parent)
    : QWidget(parent)
{
    currentAngle = 45;
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
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

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);

    painter.translate(0, rect().height());
    painter.drawPie(QRect(-35, -35, 70, 70), 0, 90 * 16);
    painter.rotate(-currentAngle);
    painter.drawRect(QRect(30, -5, 20, 10));
}
