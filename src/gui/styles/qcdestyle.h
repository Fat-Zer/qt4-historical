/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the style module of the Qt Toolkit.
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


#ifndef QCDESTYLE_H
#define QCDESTYLE_H

#include "QtGui/qmotifstyle.h"

#if !defined(QT_NO_STYLE_CDE) || defined(QT_PLUGIN)

#if defined(QT_PLUGIN)
#define Q_GUI_EXPORT_STYLE_CDE
#else
#define Q_GUI_EXPORT_STYLE_CDE Q_GUI_EXPORT
#endif

class Q_GUI_EXPORT_STYLE_CDE QCDEStyle : public QMotifStyle
{
    Q_OBJECT
public:

    explicit QCDEStyle(bool useHighlightCols = false);
    virtual ~QCDEStyle();

    int pixelMetric(PixelMetric metric, const QStyleOption *option = 0,
                    const QWidget *widget = 0) const;

    void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p,
                             const QWidget *w = 0) const;

    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                        const QWidget *w = 0) const;

    QPalette standardPalette() const;

};

#endif // QT_NO_STYLE_CDE

#endif // QCDESTYLE_H
