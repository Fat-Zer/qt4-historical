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

#ifndef QSIZEGRIP_H
#define QSIZEGRIP_H

#include "QtGui/qwidget.h"

#ifndef QT_NO_SIZEGRIP

class QSizeGripPrivate;
class Q_GUI_EXPORT QSizeGrip : public QWidget
{
    Q_OBJECT
public:
    explicit QSizeGrip(QWidget *parent);
    ~QSizeGrip();

    QSize sizeHint() const;

    void setVisible(bool);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    bool eventFilter(QObject *, QEvent *);
    bool event(QEvent *);

#ifdef QT3_SUPPORT
    QT3_SUPPORT_CONSTRUCTOR QSizeGrip(QWidget *parent, const char *name);
#endif
private:
    Q_DECLARE_PRIVATE(QSizeGrip)
    Q_DISABLE_COPY(QSizeGrip)
};

#endif // QT_NO_SIZEGRIP

#endif // QSIZEGRIP_H
