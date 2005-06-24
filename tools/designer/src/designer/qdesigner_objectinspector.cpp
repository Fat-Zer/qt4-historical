/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#include "qdesigner.h"
#include "qdesigner_objectinspector.h"
#include "qdesigner_workbench.h"

#include <QtDesigner/QtDesigner>
#include <QtDesigner/QDesignerComponents>

QDesignerObjectInspector::QDesignerObjectInspector(QDesignerWorkbench *workbench)
    : QDesignerToolWindow(workbench)
{
    setObjectName(QLatin1String("ObjectInspector"));
    QDesignerObjectInspectorInterface *widget = QDesignerComponents::createObjectInspector(workbench->core(), this);
    workbench->core()->setObjectInspector(widget);

    setCentralWidget(widget);

    setWindowTitle(tr("Object Inspector"));
}

QDesignerObjectInspector::~QDesignerObjectInspector()
{
}

QRect QDesignerObjectInspector::geometryHint() const
{
    QRect g = workbench()->availableGeometry();
    int margin = workbench()->marginHint();

    QSize sz(g.width() * 1/4, g.height() * 1/6);

    return QRect((g.width() - sz.width() - margin), margin,
                  sz.width(), sz.height());
}
