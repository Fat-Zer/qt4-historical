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

#include "abstractpropertyeditor.h"

/*!
    \class QDesignerPropertyEditorInterface
    \brief The QDesignerPropertyEditorInterface class provides an interface that is used to
    control Qt Designer's property editor component.
    \inmodule QtDesigner
*/

/*!
*/
QDesignerPropertyEditorInterface::QDesignerPropertyEditorInterface(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
}

/*!
*/
QDesignerPropertyEditorInterface::~QDesignerPropertyEditorInterface()
{
}

/*!
*/
QDesignerFormEditorInterface *QDesignerPropertyEditorInterface::core() const
{
    return 0;
}

/*!
    \fn virtual bool QDesignerPropertyEditorInterface::isReadOnly() const = 0
*/

/*!
    \fn virtual QObject *QDesignerPropertyEditorInterface::object() const = 0
*/

/*!
    \fn virtual QString QDesignerPropertyEditorInterface::currentPropertyName() const = 0
*/

/*!
    \fn void QDesignerPropertyEditorInterface::propertyChanged(const QString &name, const QVariant &value)

    This signal is emitted whenever a property changes in the editor.
    The property changed and its new value are specified by \a name and \a value
    respectively.
*/

/*!
    \fn virtual void QDesignerPropertyEditorInterface::setObject(QObject *object) = 0
*/

/*!
    \fn virtual void QDesignerPropertyEditorInterface::setPropertyValue(const QString &name, const QVariant &value, bool changed = true) = 0
*/

/*!
    \fn virtual void QDesignerPropertyEditorInterface::setReadOnly(bool readOnly) = 0
*/
