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

#ifndef Q3OBJECTDICT_H
#define Q3OBJECTDICT_H

#ifndef QT_H
#include "QtCore/qmetaobject.h"
#include "Qt3Support/q3asciidict.h"
#endif // QT_H


//
// The object dictionary is a collection of QMetaObjects
//

class Q_COMPAT_EXPORT Q3ObjectDictionary : public Q3AsciiDict<QMetaObject>
{
public:
    Q3ObjectDictionary(int size=17,bool cs=true,bool ck=true)
	: Q3AsciiDict<QMetaObject>(size,cs,ck) {}
    Q3ObjectDictionary( const Q3ObjectDictionary &dict )
	: Q3AsciiDict<QMetaObject>(dict) {}
   ~Q3ObjectDictionary() { clear(); }
    Q3ObjectDictionary &operator=(const Q3ObjectDictionary &dict)
	{ return (Q3ObjectDictionary&)Q3AsciiDict<QMetaObject>::operator=(dict);}
};

#endif // Q3OBJECTDICT_H
