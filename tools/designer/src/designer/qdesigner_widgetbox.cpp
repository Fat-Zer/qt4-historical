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

#include "qdesigner.h"
#include "qdesigner_widgetbox.h"
#include "qdesigner_workbench.h"
#include "qdesigner_settings.h"

#include <QtDesigner/QtDesigner>
#include <QtDesigner/QDesignerComponents>

#include <QtCore/qdebug.h>

QDesignerWidgetBox::QDesignerWidgetBox(QDesignerWorkbench *workbench)
    : QDesignerToolWindow(workbench)
{
    setObjectName(QLatin1String("WidgetBox"));
    QDesignerWidgetBoxInterface *widget = QDesignerComponents::createWidgetBox(workbench->core(), this);
    widget->setFileName(QLatin1String(":/trolltech/widgetbox/widgetbox.xml"));
    widget->load();
    widget->setFileName(QDesignerSettings().defaultUserWidgetBoxXml());
    widget->load();

    workbench->core()->setWidgetBox(widget);

    setCentralWidget(widget);

    setWindowTitle(tr("Widget Box"));
}

QDesignerWidgetBox::~QDesignerWidgetBox()
{
}

QRect QDesignerWidgetBox::geometryHint() const
{
    QRect g = workbench()->availableGeometry();

    return QRect(workbench()->marginHint(), workbench()->marginHint(),
                 g.width() * 1/4, g.height() * 5/6);
}

Qt::DockWidgetArea QDesignerWidgetBox::dockWidgetAreaHint() const
{
    return Qt::LeftDockWidgetArea;
}
