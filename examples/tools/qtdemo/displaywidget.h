/****************************************************************************
**
** Copyright (C) 2005-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QBasicTimer>
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
    void timerEvent(QTimerEvent *event);

signals:
    void actionRequested(const QString &name);
    void displayEmpty();
    void categoryRequested(const QString &name);
    void documentationRequested(const QString &name);
    void exampleRequested(const QString &name);
    void launchRequested(const QString &name);

private:
    bool empty;
    bool emptying;
    bool updatesEnabled;
    QList<DisplayShape*> shapes;
    QBasicTimer timer;

#if defined(Q_WS_X11)
    int numFrames;
    int frameTime;
    int avgRate;
    bool testDrawSpeed;
#endif
};

#endif
