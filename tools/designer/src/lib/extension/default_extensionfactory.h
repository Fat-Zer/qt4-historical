/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef DEFAULT_EXTENSIONFACTORY_H
#define DEFAULT_EXTENSIONFACTORY_H

#include <QtDesigner/extension_global.h>
#include <QtDesigner/extension.h>

#include <QtCore/QMap>
#include <QtCore/QHash>
#include <QtCore/QPair>

class QExtensionManager;

class QT_EXTENSION_EXPORT QExtensionFactory : public QObject, public QAbstractExtensionFactory
{
    Q_OBJECT
    Q_INTERFACES(QAbstractExtensionFactory)
public:
    QExtensionFactory(QExtensionManager *parent = 0);

    virtual QObject *extension(QObject *object, const QString &iid) const;
    QExtensionManager *extensionManager() const;

private slots:
    void objectDestroyed(QObject *object);

protected:
    virtual QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;

private:
    mutable QMap< QPair<QString,QObject*>, QObject*> m_extensions;
    mutable QHash<QObject*, bool> m_extended;
};

#endif // DEFAULT_EXTENSIONFACTORY_H
