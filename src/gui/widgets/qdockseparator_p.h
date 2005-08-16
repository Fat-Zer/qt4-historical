/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech AS. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#include "QtCore/qpointer.h"
#include "QtGui/qwidget.h"

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
	QPointer<QWidget> prevFocus;
    } *state;
};

#endif // QT_NO_DOCKWIDGET

#endif // QDOCKSEPARATOR_P_H
