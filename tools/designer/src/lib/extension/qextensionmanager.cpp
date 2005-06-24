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

#include "qextensionmanager.h"

/*!
    \class QExtensionManager
    \brief The QExtensionManager class provides extension management facilities for \QD.
    \inmodule QtDesigner
*/

/*!
    Constructs an extenstion manager with the given \a parent.*/
QExtensionManager::QExtensionManager(QObject *parent)
    : QObject(parent)
{
}

/*!
    Register \a factory as an extension factory with an identifier specified by \a iid.*/
void QExtensionManager::registerExtensions(QAbstractExtensionFactory *factory, const QString &iid)
{
    if (iid.isEmpty()) {
        m_globalExtension.append(factory);
        return;
    }

    if (!m_extensions.contains(iid))
        m_extensions.insert(iid, QList<QAbstractExtensionFactory*>());

    m_extensions[iid].prepend(factory);
}

/*!
    Unregister the \a factory with the identifier specified by \a iid.*/
void QExtensionManager::unregisterExtensions(QAbstractExtensionFactory *factory, const QString &iid)
{
    if (iid.isEmpty()) {
        m_globalExtension.removeAll(factory);
    } else if (m_extensions.contains(iid)) {
        QList<QAbstractExtensionFactory*> &factories = m_extensions[iid];
        factories.removeAll(factory);

        if (factories.isEmpty())
            m_extensions.remove(iid);
    }
}

/*!
    Returns the extension for the given \a object with the identifier specified by \a iid.*/
QObject *QExtensionManager::extension(QObject *object, const QString &iid) const
{
    QList<QAbstractExtensionFactory*> l = m_extensions.value(iid);
    l += m_globalExtension;

    foreach (QAbstractExtensionFactory *factory, l) {
        if (QObject *ext = factory->extension(object, iid))
            return ext;
    }

    return 0;
}
