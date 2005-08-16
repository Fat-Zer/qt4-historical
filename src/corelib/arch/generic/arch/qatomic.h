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

#ifndef GENERIC_QATOMIC_H
#define GENERIC_QATOMIC_H

inline int q_atomic_test_and_set_int(volatile int *ptr, int expected, int newval)
{
    if (*ptr == expected) {
        *ptr = newval;
        return 1;
    }
    return 0;
}

inline int q_atomic_test_and_set_ptr(volatile void *ptr, void *expected, void *newval)
{
    if (*reinterpret_cast<void * volatile *>(ptr) == expected) {
        *reinterpret_cast<void * volatile *>(ptr) = newval;
        return 1;
    }
    return 0;
}

inline int q_atomic_increment(volatile int *ptr)
{ return ++(*ptr); }

inline int q_atomic_decrement(volatile int *ptr)
{ return --(*ptr); }

inline int q_atomic_set_int(volatile int *ptr, int newval)
{
    register int ret = *ptr;
    *ptr = newval;
    return ret;
}

inline void *q_atomic_set_ptr(volatile void *ptr, void *newval)
{
    register void *ret = *reinterpret_cast<void * volatile *>(ptr);
    *reinterpret_cast<void * volatile *>(ptr) = newval;
    return ret;
}

#endif // GENERIC_QATOMIC_H
