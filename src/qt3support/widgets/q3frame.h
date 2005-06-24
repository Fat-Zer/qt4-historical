/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#ifndef Q3FRAME_H
#define Q3FRAME_H

#include "QtGui/qframe.h"

class Q_COMPAT_EXPORT Q3Frame : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(int margin READ margin WRITE setMargin)
    Q_PROPERTY(QRect contentsRect READ contentsRect)

public:
    Q3Frame(QWidget* parent, const char* name = 0, Qt::WFlags f = 0);
    ~Q3Frame();
#ifndef qdoc
    bool        lineShapesOk()  const { return true; }
#endif

    int margin() const { return marg; }
    void setMargin(int);

    QRect contentsRect() const;
    int frameWidth() const;

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    virtual void frameChanged();
    virtual void drawFrame(QPainter *);
    virtual void drawContents(QPainter *);

private:
    Q_DISABLE_COPY(Q3Frame)

    int marg;
};

#endif // Q3FRAME_H
