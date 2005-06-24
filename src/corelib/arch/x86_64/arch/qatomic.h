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

#ifndef X86_64_QATOMIC_H
#define X86_64_QATOMIC_H

#include <QtCore/qglobal.h>

#if defined(Q_CC_GNU)

inline int q_atomic_test_and_set_int(volatile int *ptr, int expected, int newval)
{
    unsigned char ret;
    asm volatile("lock cmpxchgl %2,%3\n"
                 "sete %1\n"
                 : "=a" (newval), "=qm" (ret)
                 : "r" (newval), "m" (*ptr), "0" (expected)
                 : "memory");
    return static_cast<int>(ret);
}

inline int q_atomic_test_and_set_ptr(volatile void *ptr, void *expected, void *newval)
{
    unsigned char ret;
    asm volatile("lock cmpxchgq %2,%3\n"
                 "sete %1\n"
                 : "=a" (newval), "=qm" (ret)
                 : "r" (newval), "m" (*reinterpret_cast<volatile long *>(ptr)), "0" (expected)
                 : "memory");
    return static_cast<int>(ret);
}

inline int q_atomic_increment(volatile int *ptr)
{
    unsigned char ret;
    asm volatile("lock incl %0\n"
                 "setne %1"
                 : "=m" (*ptr), "=qm" (ret)
                 : "m" (*ptr)
                 : "memory");
    return static_cast<int>(ret);
}

inline int q_atomic_decrement(volatile int *ptr)
{
    unsigned char ret;
    asm volatile("lock decl %0\n"
                 "setne %1"
                 : "=m" (*ptr), "=qm" (ret)
                 : "m" (*ptr)
                 : "memory");
    return static_cast<int>(ret);
}

inline int q_atomic_set_int(volatile int *ptr, int newval)
{
    asm volatile("xchgl %0,%1"
                 : "=r" (newval)
                 : "m" (*ptr), "0" (newval)
                 : "memory");
    return newval;
}

inline void *q_atomic_set_ptr(volatile void *ptr, void *newval)
{
    asm volatile("xchgq %0,%1"
                 : "=r" (newval)
                 : "m" (*reinterpret_cast<volatile long *>(ptr)), "0" (newval)
                 : "memory");
    return newval;
}

#endif

#endif // X86_64_QATOMIC_H
