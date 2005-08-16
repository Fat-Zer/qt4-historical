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

#ifndef QRUBBERBAND_H
#define QRUBBERBAND_H

#include <QtGui/qwidget.h>

class QRubberBandPrivate;

class Q_GUI_EXPORT QRubberBand : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Line, Rectangle };
    explicit QRubberBand(Shape, QWidget * =0);
    ~QRubberBand();

    Shape shape() const;

    void setGeometry(const QRect &r);

    inline void setGeometry(int x, int y, int w, int h);
    inline void move(int x, int y);
    inline void move(const QPoint &p)
    { move(p.x(), p.y()); }
    inline void resize(int w, int h)
    { setGeometry(geometry().x(), geometry().y(), w, h); }
    inline void resize(const QSize &s)
    { resize(s.width(), s.height()); }


protected:

    void paintEvent(QPaintEvent *);
    void changeEvent(QEvent *);

private:
    Q_DECLARE_PRIVATE(QRubberBand)
};

inline void QRubberBand::setGeometry(int ax, int ay, int aw, int ah)
{ setGeometry(QRect(ax, ay, aw, ah)); }
inline void QRubberBand::move(int ax, int ay)
{ setGeometry(ax + geometry().x() - QWidget::x(),
              ay - geometry().y() - QWidget::y(),
              width(), height()); }

#endif // QRUBBERBAND_H
