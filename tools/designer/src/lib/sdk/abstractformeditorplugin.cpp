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

#include <QtDesigner/abstractformeditorplugin.h>

/*!
    \class QDesignerFormEditorPluginInterface
    \brief The QDesignerFormEditorPluginInterface class provides an interface that is used to
    manage plugins for \QD's form editor component.
    \inmodule QtDesigner

    \sa QDesignerFormEditorInterface
*/

/*!
    \fn virtual QDesignerFormEditorPluginInterface::~QDesignerFormEditorPluginInterface()

    Destroys the plugin interface.
*/

/*!
    \fn virtual bool QDesignerFormEditorPluginInterface::isInitialized() const = 0

    Returns true if the plugin interface is initialized; otherwise returns false.
*/

/*!
    \fn virtual void QDesignerFormEditorPluginInterface::initialize(QDesignerFormEditorInterface *core) = 0

    Initializes the plugin interface for the specified \a core interface.
*/

/*!
    \fn virtual QAction *QDesignerFormEditorPluginInterface::action() const = 0

    Returns the action associated with this interface.
*/

/*!
    \fn virtual QDesignerFormEditorInterface *QDesignerFormEditorPluginInterface::core() const = 0

    Returns the core form editor interface associated with this component.
*/
