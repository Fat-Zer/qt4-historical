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

#ifndef QDOCKWIDGET_P_H
#define QDOCKWIDGET_P_H

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

#include "private/qwidget_p.h"

class QBoxLayout;
class QDockWidgetTitle;
class QWidgetResizeHandler;

class QDockWidgetPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QDockWidget)

public:
    inline QDockWidgetPrivate()
	: QWidgetPrivate(), widget(0),
          features(QDockWidget::DockWidgetClosable
                   | QDockWidget::DockWidgetMovable
                   | QDockWidget::DockWidgetFloatable),
          allowedAreas(Qt::AllDockWidgetAreas), top(0), box(0), title(0), resizer(0)
    { }

    void init();
    void toggleView(bool); // private slot

    QWidget *widget;

    QDockWidget::DockWidgetFeatures features;
    Qt::DockWidgetAreas allowedAreas;

    QBoxLayout *top, *box;
    QDockWidgetTitle *title;

    QWidgetResizeHandler *resizer;

    QAction *toggleViewAction;
};

#endif // QDOCKWIDGET_P_H
