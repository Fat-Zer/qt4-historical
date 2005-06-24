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

#include <QtDesigner/extension.h>

/*!
    \class QAbstractExtensionFactory
    \brief The QAbstractExtensionFactory class provides the standard interface for extension
    factories in \QD.
    \inmodule QtDesigner
*/

/*!
    \fn virtual QAbstractExtensionFactory::~QAbstractExtensionFactory()

    Destroys the extension factory.
*/

/*!
    \fn virtual QObject *QAbstractExtensionFactory::extension(QObject *object, const QString &iid) const = 0

    Returns an extension for the given \a object with an extension identifier specified by \a iid.
*/


/*!
    \class QAbstractExtensionManager
    \brief The QAbstractExtensionManager class provides the abstract interface for extension
    managers in \QD.
    \inmodule QtDesigner
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
