/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QABSTRACTSLIDER_H
#define QABSTRACTSLIDER_H

#include "QtGui/qwidget.h"

class QAbstractSliderPrivate;

class Q_GUI_EXPORT QAbstractSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(int pageStep READ pageStep WRITE setPageStep)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int sliderPosition READ sliderPosition WRITE setSliderPosition NOTIFY sliderMoved)
    Q_PROPERTY(bool tracking READ hasTracking WRITE setTracking)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(bool invertedAppearance READ invertedAppearance WRITE setInvertedAppearance)
    Q_PROPERTY(bool invertedControls READ invertedControls WRITE setInvertedControls)
    Q_PROPERTY(bool sliderDown READ isSliderDown WRITE setSliderDown DESIGNABLE false)

public:
    explicit QAbstractSlider(QWidget *parent=0);
    ~QAbstractSlider();

    Qt::Orientation orientation() const;

    void setMinimum(int);
    int minimum() const;

    void setMaximum(int);
    int maximum() const;

    void setRange(int min, int max);

    void setSingleStep(int);
    int singleStep() const;

    void setPageStep(int);
    int pageStep() const;

    void setTracking(bool enable);
    bool hasTracking() const;

    void setSliderDown(bool);
    bool isSliderDown() const;

    void setSliderPosition(int);
    int sliderPosition() const;

    void setInvertedAppearance(bool);
    bool invertedAppearance() const;

    void setInvertedControls(bool);
    bool invertedControls() const;

    enum SliderAction {
        SliderNoAction,
        SliderSingleStepAdd,
        SliderSingleStepSub,
        SliderPageStepAdd,
        SliderPageStepSub,
        SliderToMinimum,
        SliderToMaximum,
        SliderMove
    };

    int value() const;

    void triggerAction(SliderAction action);

public slots:
    void setValue(int);
    void setOrientation(Qt::Orientation);

signals:
    void valueChanged(int value);

    void sliderPressed();
    void sliderMoved(int position);
    void sliderReleased();

    void rangeChanged(int min, int max);

    void actionTriggered(int action);

protected:
    void setRepeatAction(SliderAction action, int thresholdTime = 500, int repeatTime = 50);
    SliderAction repeatAction() const;

    enum SliderChange {
        SliderRangeChange,
        SliderOrientationChange,
        SliderStepsChange,
        SliderValueChange
    };
    virtual void sliderChange(SliderChange change);

    void keyPressEvent(QKeyEvent *ev);
    void timerEvent(QTimerEvent *);
    void wheelEvent(QWheelEvent *e);
    void changeEvent(QEvent *e);

#ifdef QT3_SUPPORT
public:
    inline QT3_SUPPORT int minValue() const { return minimum(); }
    inline QT3_SUPPORT int maxValue() const { return maximum(); }
    inline QT3_SUPPORT int lineStep() const { return singleStep(); }
    inline QT3_SUPPORT void setMinValue(int v) { setMinimum(v); }
    inline QT3_SUPPORT void setMaxValue(int v) { setMaximum(v); }
    inline QT3_SUPPORT void setLineStep(int v) { setSingleStep(v); }
    inline QT3_SUPPORT void setSteps(int single, int page) { setSingleStep(single); setPageStep(page); }
    inline QT3_SUPPORT void addPage() { triggerAction(SliderPageStepAdd); }
    inline QT3_SUPPORT void subtractPage() { triggerAction(SliderPageStepSub); }
    inline QT3_SUPPORT void addLine() { triggerAction(SliderSingleStepAdd); }
    inline QT3_SUPPORT void subtractLine() { triggerAction(SliderSingleStepSub); }
#endif

protected:
    QAbstractSlider(QAbstractSliderPrivate &dd, QWidget *parent=0);

private:
    Q_DISABLE_COPY(QAbstractSlider)
    Q_DECLARE_PRIVATE(QAbstractSlider)
};

#endif // QABSTRACTSLIDER_H
