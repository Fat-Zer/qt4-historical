/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QDOCKSEPARATOR_P_H
#define QDOCKSEPARATOR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qwidget.h>

#ifndef QT_NO_DOCKWIDGET

class QDockWidgetLayout;

class QDockSeparator : public QWidget
{
    Q_OBJECT
public:
    QDockSeparator(QDockWidgetLayout *dock, QWidget *parent);

    void setDock(QDockWidgetLayout *d);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    bool event(QEvent *event);

    QDockWidgetLayout *dock;
    Qt::Orientation orientation;
    bool hover;

    struct DragState {
	QPoint origin;
	QWidget *prevFocus;
    } *state;
};

#endif // QT_NO_DOCKWIDGET
#endif // QDOCKSEPARATOR_P_H
