/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the accessibility module of the Qt Toolkit.
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

#ifndef QACCESSIBLEBRIDGE_H
#define QACCESSIBLEBRIDGE_H

#include "QtCore/qplugin.h"
#include "QtCore/qfactoryinterface.h"

#ifndef QT_NO_ACCESSIBILITY

class QAccessibleInterface;

class QAccessibleBridge
{
public:
    virtual ~QAccessibleBridge() {}
    virtual void setRootObject(QAccessibleInterface *) = 0;
    virtual void notifyAccessibilityUpdate(int, QAccessibleInterface*, int) = 0;
};

struct Q_GUI_EXPORT QAccessibleBridgeFactoryInterface : public QFactoryInterface
{
    virtual QAccessibleBridge *create(const QString& name) = 0;
};

#define QAccessibleBridgeFactoryInterface_iid "com.trolltech.Qt.QAccessibleBridgeFactoryInterface"
Q_DECLARE_INTERFACE(QAccessibleBridgeFactoryInterface, QAccessibleBridgeFactoryInterface_iid)

class Q_GUI_EXPORT QAccessibleBridgePlugin : public QObject, public QAccessibleBridgeFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(QAccessibleBridgeFactoryInterface:QFactoryInterface)
public:
    explicit QAccessibleBridgePlugin(QObject *parent = 0);
    ~QAccessibleBridgePlugin();

    virtual QStringList keys() const = 0;
    virtual QAccessibleBridge *create(const QString &key) = 0;
};

#endif // QT_NO_ACCESSIBILITY

#endif // QSQLDRIVERPLUGIN_H
