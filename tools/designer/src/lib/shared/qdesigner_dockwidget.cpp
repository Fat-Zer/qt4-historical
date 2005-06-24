/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#include "qdesigner_dockwidget_p.h"
#include <QtDesigner/QDesignerFormWindowInterface>

#include <QtGui/QMainWindow>

QDesignerDockWidget::QDesignerDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
}

QDesignerDockWidget::~QDesignerDockWidget()
{
}

Qt::DockWidgetArea QDesignerDockWidget::dockWidgetArea() const
{
    if (QMainWindow *mainWindow = qobject_cast<QMainWindow*>(parentWidget()))
        return mainWindow->dockWidgetArea(const_cast<QDesignerDockWidget*>(this));

    return Qt::DockWidgetArea(0);
}

void QDesignerDockWidget::setDockWidgetArea(Qt::DockWidgetArea dockWidgetArea)
{
    if (QMainWindow *mainWindow = qobject_cast<QMainWindow*>(parentWidget())) {
        mainWindow->removeDockWidget(this);
        mainWindow->addDockWidget(dockWidgetArea, this);
    }
}

bool QDesignerDockWidget::inMainWindow() const
{
    return qobject_cast<QMainWindow*>(parentWidget()) != 0;
}

