/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the accessibility module of the Qt Toolkit.
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

#include "qaccessible.h"
#include "qaccessiblebridge.h"

#ifndef QT_NO_ACCESSIBILITY

#include "qcoreapplication.h"
#include "qmutex.h"
#include "qvector.h"
#include "private/qfactoryloader_p.h"

#include <stdlib.h>

#ifndef QT_NO_COMPONENT
Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader,
    (QAccessibleBridgeFactoryInterface_iid, QCoreApplication::libraryPaths(), "/accessiblebridge"))
#endif
Q_GLOBAL_STATIC(QVector<QAccessibleBridge *>, bridges)
static bool isInit = false;

void QAccessible::initialize()
{
    if (isInit)
        return;
    isInit = true;

    if (qgetenv("QT_ACCESSIBILITY") != "1")
        return;
#ifndef QT_NO_COMPONENT
    const QStringList l = loader()->keys();
    for (int i = 0; i < l.count(); ++i) {
        if (QAccessibleBridgeFactoryInterface *factory =
                qobject_cast<QAccessibleBridgeFactoryInterface*>(loader()->instance(l.at(i)))) {
            QAccessibleBridge * bridge = factory->create(l.at(i));
            if (bridge)
                bridges()->append(bridge);
        }
    }
#endif
}

void QAccessible::cleanup()
{
    qDeleteAll(*bridges());
}

void QAccessible::updateAccessibility(QObject *o, int who, Event reason)
{
    Q_ASSERT(o);

    if (updateHandler) {
        updateHandler(o, who, reason);
        return;
    }

    initialize();
    if (bridges()->isEmpty())
        return;

    QAccessibleInterface *iface = QAccessible::queryAccessibleInterface(o);
    if (!iface)
        return;

    for (int i = 0; i < bridges()->count(); ++i)
        bridges()->at(i)->notifyAccessibilityUpdate(reason, iface, who);
    delete iface;
}

void QAccessible::setRootObject(QObject *o)
{
    if (rootObjectHandler) {
        rootObjectHandler(o);
        return;
    }

    initialize();
    if (bridges()->isEmpty())
        return;

    if (!o)
        return;

    for (int i = 0; i < bridges()->count(); ++i) {
        QAccessibleInterface *iface = QAccessible::queryAccessibleInterface(o);
        bridges()->at(i)->setRootObject(iface);
    }
}

#endif
