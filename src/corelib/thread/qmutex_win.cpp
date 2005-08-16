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

#include <windows.h>

#include "qmutex.h"
#include <qatomic.h>
#include "qmutex_p.h"

QMutexPrivate::QMutexPrivate(QMutex::RecursionMode mode)
    : lock(0), owner(0), count(0), recursive(mode == QMutex::Recursive),
      event(QT_WA_INLINE(CreateEventW(0, false, false, 0),
                         CreateEventA(0, false, false, 0)))
{
    if (!event)
        qWarning("QMutexPrivate::QMutexPrivate(): Creating event failed");
}

QMutexPrivate::~QMutexPrivate()
{ CloseHandle(event); }

ulong QMutexPrivate::self()
{ return GetCurrentThreadId(); }

void QMutexPrivate::wait()
{ 
    if (WaitForSingleObject(event, INFINITE) != WAIT_OBJECT_0)
        qWarning("QMutexPrivate::wait(): Waiting on event failed");
}

void QMutexPrivate::wakeUp()
{ SetEvent(event); }
