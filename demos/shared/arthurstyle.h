/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef ARTHURSTYLE_H
#define ARTHURSTYLE_H

#include <QtGui/qwindowsstyle.h>

#include <qpainter.h>
#include <qpushbutton.h>
#include <qstyleoption.h>

class ArthurGroupBoxStyleOption : public QStyleOption
{
public:
    enum { Type = SO_CustomBase + 1 };
    enum { Version = 1 };

    QString title;

    ArthurGroupBoxStyleOption() : QStyleOption(Version, Type) {}

    ArthurGroupBoxStyleOption(const ArthurGroupBoxStyleOption &other)
        : QStyleOption(Version, Type) { *this = other; }

protected:
    ArthurGroupBoxStyleOption(int version);
};

class ArthurStyle : public QWindowsStyle
{
public:
    ArthurStyle();

    void drawHoverRect(QPainter *painter, const QRect &rect) const;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget = 0) const;
//     void drawControl(ControlElement element, const QStyleOption *option,
//                      QPainter *painter, const QWidget *widget) const;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option,
                            QPainter *painter, const QWidget *widget) const;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const;

    QRect subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget) const;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt,
                         SubControl sc, const QWidget *widget) const;

//     SubControl hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option,
// 				     const QPoint &pos, const QWidget *widget = 0) const;

    int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const;

    void polish(QPalette &palette);
    void polish(QWidget *widget);
    void unpolish(QWidget *widget);
};

#endif
