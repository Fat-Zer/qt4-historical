/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt3Support module of the Qt Toolkit.
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

#ifndef Q3OBJECTDICT_H
#define Q3OBJECTDICT_H

#ifndef QT_H
#include "QtCore/qmetaobject.h"
#include "Qt3Support/q3asciidict.h"
#endif // QT_H

QT_MODULE(Qt3SupportLight)

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
