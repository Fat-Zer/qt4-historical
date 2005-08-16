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

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPainterPath>
#include <QWidget>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(const QPainterPath &path, QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setFillRule(Qt::FillRule rule);
    void setFillGradient(const QColor &color1, const QColor &color2);
    void setPenWidth(int width);
    void setPenColor(const QColor &color);
    void setRotationAngle(int degrees);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPainterPath path;
    QColor fillColor1;
    QColor fillColor2;
    int penWidth;
    QColor penColor;
    int rotationAngle;
};

#endif
