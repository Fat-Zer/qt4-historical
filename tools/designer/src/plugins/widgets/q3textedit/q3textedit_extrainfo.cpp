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

#include "q3textedit_extrainfo.h"

#include <QtDesigner/QDesignerIconCacheInterface>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/ui4.h>

#include <Qt3Support/Q3TextEdit>

inline QHash<QString, DomProperty *> propertyMap(const QList<DomProperty *> &properties) // ### remove me
{
    QHash<QString, DomProperty *> map;

    for (int i=0; i<properties.size(); ++i) {
        DomProperty *p = properties.at(i);
        map.insert(p->attributeName(), p);
    }

    return map;
}

Q3TextEditExtraInfo::Q3TextEditExtraInfo(Q3TextEdit *widget, QDesignerFormEditorInterface *core, QObject *parent)
    : QObject(parent), m_widget(widget), m_core(core)
{}

QWidget *Q3TextEditExtraInfo::widget() const
{ return m_widget; }

QDesignerFormEditorInterface *Q3TextEditExtraInfo::core() const
{ return m_core; }

bool Q3TextEditExtraInfo::saveUiExtraInfo(DomUi *ui)
{ Q_UNUSED(ui); return false; }

bool Q3TextEditExtraInfo::loadUiExtraInfo(DomUi *ui)
{ Q_UNUSED(ui); return false; }


bool Q3TextEditExtraInfo::saveWidgetExtraInfo(DomWidget *ui_widget)
{
    Q_UNUSED(ui_widget);

    Q3TextEdit *textEdit = qobject_cast<Q3TextEdit*>(widget());
    Q_ASSERT(textEdit != 0);

    return true;
}

bool Q3TextEditExtraInfo::loadWidgetExtraInfo(DomWidget *ui_widget)
{
    Q_UNUSED(ui_widget);

    Q3TextEdit *textEdit = qobject_cast<Q3TextEdit*>(widget());
    Q_ASSERT(textEdit != 0);
    return true;
}

Q3TextEditExtraInfoFactory::Q3TextEditExtraInfoFactory(QDesignerFormEditorInterface *core, QExtensionManager *parent)
    : QExtensionFactory(parent), m_core(core)
{}

QObject *Q3TextEditExtraInfoFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerExtraInfoExtension))
        return 0;

    if (Q3TextEdit *w = qobject_cast<Q3TextEdit*>(object))
        return new Q3TextEditExtraInfo(w, m_core, parent);

    return 0;
}
