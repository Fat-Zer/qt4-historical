/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#ifndef Q3RANGECONTROL_H
#define Q3RANGECONTROL_H

#include "QtCore/qglobal.h"
#include "QtGui/qwidget.h"

#ifndef QT_NO_RANGECONTROL

class Q3RangeControlPrivate;

class Q_COMPAT_EXPORT Q3RangeControl
{
public:
    Q3RangeControl();
    Q3RangeControl(int minValue, int maxValue,
                   int lineStep, int pageStep, int value);
    virtual ~Q3RangeControl();

    int                value()                const;
    void        setValue(int);
    void        addPage();
    void        subtractPage();
    void        addLine();
    void        subtractLine();

    int                minValue()        const;
    int                maxValue()        const;
    void        setRange(int minValue, int maxValue);
    void        setMinValue(int minVal);
    void        setMaxValue(int minVal);

    int                lineStep()        const;
    int                pageStep()        const;
    void        setSteps(int line, int page);

    int                bound(int) const;

protected:
    int                positionFromValue(int val, int space) const;
    int                valueFromPosition(int pos, int space) const;
    void        directSetValue(int val);
    int                prevValue()        const;

    virtual void valueChange();
    virtual void rangeChange();
    virtual void stepChange();

private:
    int                minVal, maxVal;
    int                line, page;
    int                val, prevVal;

    Q3RangeControlPrivate * d;

private:
    Q_DISABLE_COPY(Q3RangeControl)
};


inline int Q3RangeControl::value() const
{ return val; }

inline int Q3RangeControl::prevValue() const
{ return prevVal; }

inline int Q3RangeControl::minValue() const
{ return minVal; }

inline int Q3RangeControl::maxValue() const
{ return maxVal; }

inline int Q3RangeControl::lineStep() const
{ return line; }

inline int Q3RangeControl::pageStep() const
{ return page; }


#endif // QT_NO_RANGECONTROL

#ifndef QT_NO_SPINWIDGET

class Q3SpinWidgetPrivate;
class Q_COMPAT_EXPORT Q3SpinWidget : public QWidget
{
    Q_OBJECT
public:
    Q3SpinWidget(QWidget* parent=0, const char* name=0);
    ~Q3SpinWidget();

    void         setEditWidget(QWidget * widget);
    QWidget *         editWidget();

    QRect upRect() const;
    QRect downRect() const;

    void setUpEnabled(bool on);
    void setDownEnabled(bool on);

    bool isUpEnabled() const;
    bool isDownEnabled() const;

    enum ButtonSymbols { UpDownArrows, PlusMinus };
    virtual void        setButtonSymbols(ButtonSymbols bs);
    ButtonSymbols        buttonSymbols() const;

    void arrange();

signals:
    void stepUpPressed();
    void stepDownPressed();

public slots:
    void stepUp();
    void stepDown();

protected:
    void mousePressEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent* ev);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *);
#endif
    void changeEvent(QEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void timerDone();
    void timerDoneEx();

private:
    Q3SpinWidgetPrivate * d;

    void updateDisplay();

private:
    Q_DISABLE_COPY(Q3SpinWidget)
};

#endif // QT_NO_SPINWIDGET

#endif // QRANGECONTROL_H
