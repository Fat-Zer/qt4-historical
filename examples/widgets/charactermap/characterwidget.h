/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
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

#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QFont>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QWidget>

class QMouseEvent;
class QPaintEvent;

class CharacterWidget : public QWidget
{
    Q_OBJECT

public:
    CharacterWidget(QWidget *parent = 0);
    QSize sizeHint() const;

public slots:
    void updateFont(const QString &fontFamily);
    void updateStyle(const QString &fontStyle);

signals:
    void characterSelected(const QString &character);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QFont displayFont;
    int lastKey;
};

#endif
