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

#include "spacer_propertysheet.h"
#include "qdesigner_widget_p.h"
#include "formwindow.h"
#include "spacer_widget_p.h"

#include <QtDesigner/QExtensionManager>

#include <QtGui/QLayout>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/qdebug.h>

using namespace qdesigner_internal;

SpacerPropertySheet::SpacerPropertySheet(Spacer *object, QObject *parent)
    : QDesignerPropertySheet(object, parent)
{
    m_fakeProperties.clear();

    for (int i=0; i<count(); ++i)
        setVisible(i, false);

    setVisible(indexOf(QLatin1String("orientation")), true);
    setVisible(indexOf(QLatin1String("sizeType")), true);
    setVisible(indexOf(QLatin1String("sizeHint")), true);
}

SpacerPropertySheet::~SpacerPropertySheet()
{
}

void SpacerPropertySheet::setProperty(int index, const QVariant &value)
{
    QDesignerPropertySheet::setProperty(index, value);
}


SpacerPropertySheetFactory::SpacerPropertySheetFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{
}

QObject *SpacerPropertySheetFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerPropertySheetExtension))
        return 0;

    if (Spacer *o = qobject_cast<Spacer*>(object))
        return new SpacerPropertySheet(o, parent);

    return 0;
}
