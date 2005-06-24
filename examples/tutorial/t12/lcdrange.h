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

/****************************************************************
**
** Definition of LCDRange class, Qt tutorial 12
**
****************************************************************/

#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>

class QLabel;
class QSlider;

class LCDRange : public QWidget
{
    Q_OBJECT

public:
    LCDRange(QWidget *parent = 0);
    LCDRange(const QString &text, QWidget *parent = 0);

    int value() const;
    QString text() const;

public slots:
    void setValue(int value);
    void setRange(int minValue, int maxValue);
    void setText(const QString &text);

signals:
    void valueChanged(int newValue);

private:
    void init();

    QSlider *slider;
    QLabel *label;
};

#endif // LCDRANGE_H
