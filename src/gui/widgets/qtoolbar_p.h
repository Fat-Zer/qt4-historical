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

#ifndef QTOOLBAR_P_H
#define QTOOLBAR_P_H

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

#include <qaction.h>
#include <qwidget.h>
#include <qtoolbar.h>

#include <private/qwidget_p.h>

/*
    internal class to associate a widget with an action
*/
class QToolBarWidgetAction : public QAction
{
    Q_OBJECT

    QWidget *_widget;

public:
    inline QToolBarWidgetAction(QWidget *widget, QWidget *parent)
        : QAction(parent), _widget(widget)
    {
        setText(_widget->objectName().isEmpty()
            ? QString::fromLatin1(_widget->metaObject()->className())
                : _widget->objectName());
        setVisible(!(widget->isHidden() && widget->testAttribute(Qt::WA_WState_ExplicitShowHide)));
    }

    inline QWidget *widget() const
    { return _widget; }
};

struct QToolBarItem {
    QAction *action;
    QWidget *widget;
    uint hidden : 1; // toolbar too small to show this item
};

class QToolBarExtension;
class QToolBarHandle;

class QToolBarPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QToolBar)

public:
    inline QToolBarPrivate()
        : explicitIconSize(false), explicitToolButtonStyle(false), movable(false),
          allowedAreas(Qt::AllToolBarAreas), orientation(Qt::Horizontal),
          toolButtonStyle(Qt::ToolButtonIconOnly),
          handle(0), extension(0), ignoreActionAddedEvent(false)
    { }

    void init();
    void actionTriggered();
    void toggleView(bool b);
    void updateIconSize(const QSize &sz);
    void updateToolButtonStyle(Qt::ToolButtonStyle style);
    QToolBarItem createItem(QAction *action);
    int indexOf(QAction *action) const;

    bool explicitIconSize;
    bool explicitToolButtonStyle;
    bool movable;
    Qt::ToolBarAreas allowedAreas;
    Qt::Orientation orientation;
    Qt::ToolButtonStyle toolButtonStyle;
    QSize iconSize;

    QToolBarHandle *handle;
    QToolBarExtension *extension;

    QList<QToolBarItem> items;
    bool ignoreActionAddedEvent;

    QAction *toggleViewAction;
};

static inline int pick(Qt::Orientation o, const QPoint &p)
{ return o == Qt::Horizontal ? p.x() : p.y(); }

static inline int pick(Qt::Orientation o, const QSize &s)
{ return o == Qt::Horizontal ? s.width() : s.height(); }

#endif // QTOOLBAR_P_H
