/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the core module of the Qt Toolkit.
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

#ifndef QTHREAD_P_H
#define QTHREAD_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of QAbstractItemModel*.  This header file may change from version
// to version without notice, or even be removed.
//
// We mean it.
//
//

#include "qplatformdefs.h"
#include <private/qobject_p.h>
#include "qmutex.h"
#include "qstack.h"
#include "qthread.h"
#include "qwaitcondition.h"

class QAbstractEventDispatcher;
class QEventLoop;

class QPostEvent
{
public:
    QObject *receiver;
    QEvent *event;
    inline QPostEvent()
        : receiver(0), event(0)
    { }
    inline QPostEvent(QObject *r, QEvent *e)
        : receiver(r), event(e)
    { }
};

class QPostEventList : public QList<QPostEvent>
{
public:
    int offset;
    QMutex mutex;

    inline QPostEventList()
        : QList<QPostEvent>(), offset(0)
    { }
};

class Q_CORE_EXPORT QThreadData
{
public:
    QThreadData();
    ~QThreadData();

    static QThreadData *get(QThread *thread);

    int id;
    bool quitNow, allowDeferredDelete;
    QAbstractEventDispatcher *eventDispatcher;
    QStack<QEventLoop *> eventLoops;
    QPostEventList postEventList;
    void **tls;
};

class QThreadPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QThread)

public:
    QThreadPrivate();

    mutable QMutex mutex;

    bool running;
    bool finished;
    bool terminated;

    uint stackSize;

    static void setCurrentThread(QThread *thread);

    static QThread *threadForId(int id);

#ifdef Q_OS_UNIX
    pthread_t thread_id;
    QWaitCondition thread_done;

    static void *start(void *arg);
    static void finish(void *arg);
#endif

#ifdef Q_OS_WIN32
    HANDLE handle;
    unsigned int id;
    int waiters;
    bool terminationEnabled, terminatePending;

    static unsigned int __stdcall start(void *);
    static void finish(void *, bool lockAnyway=true);
#endif // Q_OS_WIN32

    QThreadData data;
};

#endif // QTHREAD_P_H
