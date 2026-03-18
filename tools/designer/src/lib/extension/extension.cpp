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

#include <QtDesigner/extension.h>

/*!
    \class QAbstractExtensionFactory
    \brief The QAbstractExtensionFactory class provides the standard interface for extension
    factories in Qt Designer.
    \inmodule QtDesigner

    In \QD, extension factories are used to look up and create named extensions as they are
    required. QAbstractExtensionFactory provides a default implementation of an extension
    factory that is 

    \sa QAbstractExtensionManager
*/

/*!
    \fn virtual QAbstractExtensionFactory::~QAbstractExtensionFactory()

    Destroys the extension factory.
*/

/*!
    \fn virtual QObject *QAbstractExtensionFactory::extension(QObject *object, const QString &iid) const = 0

    Returns an extension specified by \a iid for the given \a object.
*/


/*!
    \class QAbstractExtensionManager
    \brief The QAbstractExtensionManager class provides the abstract interface for extension
    managers in Qt Designer.
    \inmodule QtDesigner

    In \QD, the QAbstract

    \sa QAbstractExtensionFactory
*/

/*!
    \fn virtual QAbstractExtensionManager::~QAbstractExtensionManager()

    Destroys the extension manager.
*/

/*!
    \fn virtual void QAbstractExtensionManager::registerExtensions(QAbstractExtensionFactory *factory, const QString &iid) = 0
*/

/*!
    \fn virtual void QAbstractExtensionManager::unregisterExtensions(QAbstractExtensionFactory *factory, const QString &iid) = 0
*/

/*!
    \fn virtual QObject *QAbstractExtensionManager::extension(QObject *object, const QString &iid) const = 0
*/
