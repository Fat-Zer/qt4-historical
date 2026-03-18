/****************************************************************************
 **
 ** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
 **
 ** This file is part of the QtGui module of the Qt Toolkit.
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

#include "qdecorationplugin_qws.h"
#include "qdecoration_qws.h"

/*!
    \class QDecorationPlugin
    \brief The QDecorationPlugin class provides an abstract base for custom QDecoration plugins.

    \ingroup plugins

    The decoration plugin is a simple plugin interface that makes it easy
    to create custom decorations that can be loaded dynamically into
    applications with a QDecorationFactory.

    Writing a decoration plugin is achieved by subclassing this base class,
    reimplementing the pure virtual functions keys() and create(), and
    exporting the class with the Q_EXPORT_PLUGIN() macro. See
    \l{How to Create Qt Plugins} for details.

    This class is only available in Qt/Embedded.
*/

/*!
    \fn QStringList QDecorationPlugin::keys() const

    Returns the list of decoration keys this plugin supports.

    These keys are usually the class names of the custom decoration that
    are implemented in the plugin.

    \sa create()
*/

/*!
    \fn QDecoration *QDecorationPlugin::create(const QString &key)

    Creates and returns a QDecoration object for the decoration key \a key. The
    decoration key is usually the class name of the required decoration.

    \sa keys()
*/

/*!
    Constructs a decoration plugin with parent \a parent. This is
    invoked automatically by the Q_EXPORT_PLUGIN() macro.
*/
QDecorationPlugin::QDecorationPlugin(QObject *parent)
    : QObject(parent)
{
}

/*!
    Destroys the decoration plugin.

    You never have to call this explicitly. Qt destroys a plugin
    automatically when it is no longer used.
*/
QDecorationPlugin::~QDecorationPlugin()
{
}
