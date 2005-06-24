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

#ifndef PROPERTYSHEET_H
#define PROPERTYSHEET_H

#include <QtDesigner/extension.h>

class QVariant;

class QDesignerPropertySheetExtension
{
public:
    virtual ~QDesignerPropertySheetExtension() {}

    virtual int count() const = 0;

    virtual int indexOf(const QString &name) const = 0;

    virtual QString propertyName(int index) const = 0;
    virtual QString propertyGroup(int index) const = 0;
    virtual void setPropertyGroup(int index, const QString &group) = 0;

    virtual bool hasReset(int index) const = 0;
    virtual bool reset(int index) = 0;

    virtual bool isVisible(int index) const = 0;
    virtual void setVisible(int index, bool b) = 0;

    virtual bool isAttribute(int index) const = 0;
    virtual void setAttribute(int index, bool b) = 0;

    virtual QVariant property(int index) const = 0;
    virtual void setProperty(int index, const QVariant &value) = 0;

    virtual bool isChanged(int index) const = 0;
    virtual void setChanged(int index, bool changed) = 0;
};
Q_DECLARE_EXTENSION_INTERFACE(QDesignerPropertySheetExtension, "com.trolltech.Qt.Designer.PropertySheet")

#endif // PROPERTYSHEET_H
