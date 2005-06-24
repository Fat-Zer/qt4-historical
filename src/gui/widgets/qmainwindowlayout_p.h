/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QMAINWINDOWLAYOUT_P_H
#define QMAINWINDOWLAYOUT_P_H

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

#include "qmainwindow.h"

#include <qlayout.h>
#include <qvector.h>

class QToolBar;
class QDockWidget;
class QDockWidgetLayout;

class QMainWindowLayout : public QLayout
{
    Q_OBJECT

public:
    explicit QMainWindowLayout(QMainWindow *mainwindow);
    ~QMainWindowLayout();

    QLayoutItem *statusbar;
    QStatusBar *statusBar() const;
    void setStatusBar(QStatusBar *sb);

    QWidget *centralWidget() const;
    void setCentralWidget(QWidget *cw);

    void addToolBarBreak(Qt::ToolBarArea area);
    void insertToolBarBreak(QToolBar *before);
    void addToolBar(Qt::ToolBarArea area, QToolBar *toolbar, bool needAddChildWidget = true);
    void insertToolBar(QToolBar *before, QToolBar *toolbar);
    Qt::ToolBarArea toolBarArea(QToolBar *toolbar) const;

    QDockWidgetLayout *layoutForArea(Qt::DockWidgetArea area);
    void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget,
                       Qt::Orientation orientation);
    void splitDockWidget(QDockWidget *after, QDockWidget *dockwidget,
                         Qt::Orientation orientation);
    Qt::DockWidgetArea dockWidgetArea(QDockWidget *dockwidget) const;

    enum { // sentinel values used to validate state data
        VersionMarker = 0xff,
        ToolBarStateMarker = 0xfe,
        DockWidgetStateMarker = 0xfd
    };
    void saveState(QDataStream &stream) const;
    bool restoreState(QDataStream &stream);

    // QLayout interface
    void addItem(QLayoutItem *item);
    void setGeometry(const QRect &r);
    QLayoutItem *itemAt(int index) const;
    QLayoutItem *takeAt(int index);
    int count() const;

    QSize sizeHint() const;
    QSize minimumSize() const;
    mutable QSize szHint;
    mutable QSize minSize;

    void invalidate();

    void removeRecursive(QDockWidget *dockwidget);


    // utility functions

    QInternal::RelayoutType relayout_type;
    void relayout(QInternal::RelayoutType type = QInternal::RelayoutNormal);

    void saveLayoutInfo();
    void resetLayoutInfo();
    void discardLayoutInfo();

    void beginConstrain();
    void endConstrain();
    int constrain(QDockWidgetLayout *dock, int delta);

    Qt::DockWidgetArea locateDockWidget(QDockWidget *dockwidget, const QPoint &mouse) const;
    QRect placeDockWidget(QDockWidget *dockwidget, const QRect &r, const QPoint &mouse);
    void dropDockWidget(QDockWidget *dockwidget, const QRect &r, const QPoint &mouse);

    int locateToolBar(QToolBar *toolbar, const QPoint &mouse) const;
    void dropToolBar(QToolBar *toolbar, const QPoint &mouse, const QPoint &offset);

    void removeToolBarInfo(QToolBar *toolbar);

    // dock/center-widget layout data
    Qt::DockWidgetArea corners[4];
    struct QMainWindowLayoutInfo
    {
	QLayoutItem *item;
	QLayoutItem *sep;
	QSize size;
	uint is_dummy : 1;
    };
    QVector<QMainWindowLayoutInfo> layout_info, *save_layout_info;

    // toolbar layout data
    struct ToolBarLayoutInfo
    {
	QLayoutItem *item;
	QPoint pos;
        QSize size;
	QPoint offset;
    };

    struct ToolBarLineInfo
    {
        int pos;
        QList<ToolBarLayoutInfo> list;
    };

    /*
      helpers to return the index of next/prev visible toolbar... they
      return -1 if none is found
    */
    static int nextVisible(int index, const ToolBarLineInfo &lineInfo);
    static int prevVisible(int index, const ToolBarLineInfo &lineInfo);

    QList<ToolBarLineInfo> tb_layout_info, *save_tb_layout_info;
};

#endif // QMAINWINDOWLAYOUT_P_H
