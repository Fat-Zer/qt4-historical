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


#ifndef QDIAL_H
#define QDIAL_H

#include "QtGui/qabstractslider.h"

#ifndef QT_NO_DIAL

class QDialPrivate;

class Q_GUI_EXPORT QDial: public QAbstractSlider
{
    Q_OBJECT

    Q_PROPERTY(bool wrapping READ wrapping WRITE setWrapping)
    Q_PROPERTY(int notchSize READ notchSize)
    Q_PROPERTY(qreal notchTarget READ notchTarget WRITE setNotchTarget)
    Q_PROPERTY(bool notchesVisible READ notchesVisible WRITE setNotchesVisible)
public:
    explicit QDial(QWidget *parent = 0);

    ~QDial();

    bool wrapping() const;

    int notchSize() const;

    void setNotchTarget(double target);
    qreal notchTarget() const;
    bool notchesVisible() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void setNotchesVisible(bool visible);
    void setWrapping(bool on);

protected:
    void resizeEvent(QResizeEvent *re);
    void paintEvent(QPaintEvent *pe);

    void mousePressEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);

    void sliderChange(SliderChange change);

#ifdef QT3_SUPPORT
public:
    QT3_SUPPORT_CONSTRUCTOR QDial(int minValue, int maxValue, int pageStep, int value,
                                QWidget* parent = 0, const char* name = 0);
    QT3_SUPPORT_CONSTRUCTOR QDial(QWidget *parent, const char *name);

signals:
    QT_MOC_COMPAT void dialPressed();
    QT_MOC_COMPAT void dialMoved(int value);
    QT_MOC_COMPAT void dialReleased();
#endif

private:
    Q_DECLARE_PRIVATE(QDial)
    Q_DISABLE_COPY(QDial)
};

#endif  // QT_NO_DIAL

#endif // QDIAL_H
