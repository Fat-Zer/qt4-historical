/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

#include "qlayoutwidget_propertysheet.h"
#include "qlayout_widget_p.h"
#include "formwindow.h"
#include "formeditor.h"

#include <QtDesigner/QExtensionManager>

#include <QLayout>

using namespace qdesigner_internal;

QLayoutWidgetPropertySheet::QLayoutWidgetPropertySheet(QLayoutWidget *object, QObject *parent)
    : QDesignerPropertySheet(object, parent)
{
    m_fakeProperties.clear();
}

QLayoutWidgetPropertySheet::~QLayoutWidgetPropertySheet()
{
}

bool QLayoutWidgetPropertySheet::isVisible(int index) const
{
    if (propertyGroup(index) == QLatin1String("Layout"))
        return QDesignerPropertySheet::isVisible(index);
    return false;
}

void QLayoutWidgetPropertySheet::setProperty(int index, const QVariant &value)
{
    QDesignerPropertySheet::setProperty(index, value);
}

bool QLayoutWidgetPropertySheet::dynamicPropertiesAllowed() const
{
    return false;
}

QLayoutWidgetPropertySheetFactory::QLayoutWidgetPropertySheetFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{
}

QObject *QLayoutWidgetPropertySheetFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerPropertySheetExtension))
        return 0;

    if (QLayoutWidget *o = qobject_cast<QLayoutWidget*>(object))
        return new QLayoutWidgetPropertySheet(o, parent);

    return 0;
}
