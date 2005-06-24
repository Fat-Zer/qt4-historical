/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QRADIOBUTTON_H
#define QRADIOBUTTON_H

#include "QtGui/qabstractbutton.h"

#ifndef QT_NO_RADIOBUTTON

class Q_GUI_EXPORT QRadioButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit QRadioButton(QWidget *parent=0);
    explicit QRadioButton(const QString &text, QWidget *parent=0);

    QSize sizeHint() const;

protected:
    bool hitButton(const QPoint &) const;
    void paintEvent(QPaintEvent *);

#ifdef QT3_SUPPORT
public:
    QT3_SUPPORT_CONSTRUCTOR QRadioButton(QWidget *parent, const char* name);
    QT3_SUPPORT_CONSTRUCTOR QRadioButton(const QString &text, QWidget *parent, const char* name);
#endif

private:
    Q_DISABLE_COPY(QRadioButton)
};

#endif // QT_NO_RADIOBUTTON

#endif // QRADIOBUTTON_H
