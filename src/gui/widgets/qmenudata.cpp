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
#include "qmenudata.h"

#ifdef QT3_SUPPORT
#include <qaction.h>
#include <private/qaction_p.h>

/*!
    \class QMenuItem
    \brief The QMenuItem class represents an item in a menu.

    \compat

    Use QAction instead.
*/

/*!
    \compat
    Constructs a new menu item.
*/
QMenuItem::QMenuItem() : QAction((QWidget*)0)
{
}

void QMenuItem::setId(int id)
{
    d_func()->param = d_func()->id = id;
}

/*!
    \compat
    Returns the menu item's ID.
*/
int QMenuItem::id() const
{
    return d_func()->id;
}

void QMenuItem::setSignalValue(int param)
{
    d_func()->param = param;
}

/*!
    \compat
    Returns the signal value for the menu item.
*/
int QMenuItem::signalValue() const
{
    return d_func()->param;
}
#endif
