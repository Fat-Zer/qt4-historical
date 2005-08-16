/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#ifndef Q3SORTEDLIST_H
#define Q3SORTEDLIST_H

#include "Qt3Support/q3ptrlist.h"

template<class type>
class Q3SortedList : public Q3PtrList<type>
{
public:
    Q3SortedList() {}
    Q3SortedList( const Q3SortedList<type> &l ) : Q3PtrList<type>(l) {}
    ~Q3SortedList() { this->clear(); }
    Q3SortedList<type> &operator=(const Q3SortedList<type> &l)
      { return (Q3SortedList<type>&)Q3PtrList<type>::operator=(l); }

    virtual int compareItems( Q3PtrCollection::Item s1, Q3PtrCollection::Item s2 )
      { if ( *((type*)s1) == *((type*)s2) ) return 0; return ( *((type*)s1) < *((type*)s2) ? -1 : 1 ); }
};

#endif
