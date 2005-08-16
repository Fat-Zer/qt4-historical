/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the core module of the Qt Toolkit.
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

#ifndef QPAIR_H
#define QPAIR_H

#include "QtCore/qdatastream.h"

template <class T1, class T2>
struct QPair
{
    typedef T1 first_type;
    typedef T2 second_type;

    QPair() : first(T1()), second(T2()) {}
    QPair(const T1 &t1, const T2 &t2) : first(t1), second(t2) {}

    QPair &operator=(const QPair &other)
    { first = other.first; second = other.second; return *this; }

    T1 first;
    T2 second;
};

template <class T1, class T2>
Q_INLINE_TEMPLATE bool operator==(const QPair<T1, T2> &p1, const QPair<T1, T2> &p2)
{ return p1.first == p2.first && p1.second == p2.second; }

template <class T1, class T2>
Q_INLINE_TEMPLATE bool operator!=(const QPair<T1, T2> &p1, const QPair<T1, T2> &p2)
{ return !(p1 == p2); }

template <class T1, class T2>
Q_INLINE_TEMPLATE bool operator<(const QPair<T1, T2> &p1, const QPair<T1, T2> &p2)
{
    return p1.first < p2.first || (!(p2.first < p1.first) && p1.second < p2.second);
}

template <class T1, class T2>
Q_INLINE_TEMPLATE bool operator>(const QPair<T1, T2> &p1, const QPair<T1, T2> &p2)
{
    return p2 < p1;
}

template <class T1, class T2>
Q_INLINE_TEMPLATE bool operator<=(const QPair<T1, T2> &p1, const QPair<T1, T2> &p2)
{
    return !(p2 < p1);
}

template <class T1, class T2>
Q_INLINE_TEMPLATE bool operator>=(const QPair<T1, T2> &p1, const QPair<T1, T2> &p2)
{
    return !(p1 < p2);
}

template <class T1, class T2>
Q_OUTOFLINE_TEMPLATE QPair<T1, T2> qMakePair(const T1 &x, const T2 &y)
{
    return QPair<T1, T2>(x, y);
}

#ifndef QT_NO_DATASTREAM
template <class T1, class T2>
inline QDataStream& operator>>(QDataStream& s, QPair<T1, T2>& p)
{
    s >> p.first >> p.second;
    return s;
}

template <class T1, class T2>
inline QDataStream& operator<<(QDataStream& s, const QPair<T1, T2>& p)
{
    s << p.first << p.second;
    return s;
}
#endif

#endif // QPAIR_H
