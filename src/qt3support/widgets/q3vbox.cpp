/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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


#include "q3vbox.h"

/*!
    \class Q3VBox qvbox.h
    \brief The Q3VBox widget provides vertical geometry management of
    its child widgets.

    \compat

    All its child widgets will be placed vertically and sized
    according to their sizeHint()s.

    \img qvbox-m.png Q3VBox

    \sa QHBox
*/


/*!
    Constructs a vbox widget called \a name with parent \a parent and
    widget flags \a f.
 */
Q3VBox::Q3VBox( QWidget *parent, const char *name, Qt::WFlags f )
    :Q3HBox( FALSE, parent, name, f )
{
}
