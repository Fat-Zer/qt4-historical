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

#ifndef QMOTIFSTYLE_H
#define QMOTIFSTYLE_H

#include "QtGui/qcommonstyle.h"
#include "QtCore/qpointer.h"

#if !defined(QT_NO_STYLE_MOTIF) || defined(QT_PLUGIN)

class QPalette;
class QFocusFrame;

#if defined(QT_PLUGIN)
#define Q_GUI_EXPORT_STYLE_MOTIF
#else
#define Q_GUI_EXPORT_STYLE_MOTIF Q_GUI_EXPORT
#endif

class QMotifStylePrivate;
class Q_GUI_EXPORT_STYLE_MOTIF QMotifStyle : public QCommonStyle
{
    Q_OBJECT
public:
    explicit QMotifStyle(bool useHighlightCols=false);
    virtual ~QMotifStyle();

    void setUseHighlightColors(bool);
    bool useHighlightColors() const;

    void polish(QPalette&);
    void polish(QWidget*);
    void polish(QApplication*);

    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                        const QWidget *w = 0) const;

    void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p,
                      const QWidget *w = 0) const;

    void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p,
                            const QWidget *w = 0) const;

    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt,
                         SubControl sc, const QWidget *widget = 0) const;

    int pixelMetric(PixelMetric metric, const QStyleOption *option = 0,
                     const QWidget *widget = 0) const;

    QSize sizeFromContents(ContentsType ct, const QStyleOption *opt,
                           const QSize &contentsSize, const QWidget *widget = 0) const;

    QRect subElementRect(SubElement r, const QStyleOption *opt, const QWidget *widget = 0) const;

    QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *opt,
                           const QWidget *widget = 0) const;

    int styleHint(StyleHint hint, const QStyleOption *opt = 0, const QWidget *widget = 0,
                  QStyleHintReturn *returnData = 0) const;

    bool event(QEvent *);

    QPalette standardPalette() const;
protected:
    QPointer<QFocusFrame> focus;
private:
    Q_DISABLE_COPY(QMotifStyle)

    bool highlightCols;
};

#endif // QT_NO_STYLE_MOTIF

#endif // QMOTIFSTYLE_H
