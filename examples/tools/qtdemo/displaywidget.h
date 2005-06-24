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

#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

class DisplayShape;

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget *parent = 0);
    QSize minimumSizeHint() const;
    DisplayShape *shape(int index) const;
    int shapesCount() const;
    void appendShape(DisplayShape *shape);
    void enableUpdates();
    void insertShape(int position, DisplayShape *shape);
    void reset();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void actionRequested(const QString &name);
    void displayEmpty();
    void categoryRequested(const QString &name);
    void documentationRequested(const QString &name);
    void exampleRequested(const QString &name);
    void launchRequested(const QString &name);

private slots:
    void updateShapes();

private:
    bool empty;
    bool emptying;
    QList<DisplayShape*> shapes;
    QTimer *timer;
};

#endif
