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

#ifndef QMUTEX_H
#define QMUTEX_H

#include "QtCore/qglobal.h"

#ifndef QT_NO_THREAD

class QMutexPrivate;

class Q_CORE_EXPORT QMutex
{
    friend class QWaitCondition;
    friend class QWaitConditionPrivate;

public:
    enum RecursionMode { NonRecursive, Recursive };

    explicit QMutex(RecursionMode mode = NonRecursive);
    ~QMutex();

    void lock();
    bool tryLock();
    void unlock();

#if defined(QT3_SUPPORT)
    inline QT3_SUPPORT bool locked()
    {
        if (!tryLock())
            return true;
        unlock();
        return false;
    }
    inline QT3_SUPPORT_CONSTRUCTOR QMutex(bool recursive)
    {
        new (this) QMutex(recursive ? Recursive : NonRecursive);
    }
#endif

private:
    Q_DISABLE_COPY(QMutex)

    QMutexPrivate *d;
};

class Q_CORE_EXPORT QMutexLocker
{
public:
    inline explicit QMutexLocker(QMutex *m) : mtx(m) { relock(); }
    inline ~QMutexLocker() { unlock(); }

    inline void unlock() { if (mtx) mtx->unlock(); }

    inline void relock() { if (mtx) mtx->lock(); }

    inline QMutex *mutex() const { return mtx; }

private:
    Q_DISABLE_COPY(QMutexLocker)

    QMutex *mtx;
};

#else // QT_NO_THREAD


class Q_CORE_EXPORT QMutex
{
public:
    enum RecursionMode { NonRecursive, Recursive };

    inline explicit QMutex(RecursionMode mode = NonRecursive) { Q_UNUSED(mode); }
    inline ~QMutex() {}

    static inline void lock() {}
    static inline bool tryLock() { return true; }
    static void unlock() {}

#if defined(QT3_SUPPORT)
    static inline QT3_SUPPORT bool locked() { return false; }
#endif

private:
    Q_DISABLE_COPY(QMutex)
};

class Q_CORE_EXPORT QMutexLocker
{
public:
    inline explicit QMutexLocker(QMutex *) {}
    inline ~QMutexLocker() {}

    static inline void unlock() {}
    static void relock() {}
    static inline QMutex *mutex() { return 0; }

private:
    Q_DISABLE_COPY(QMutexLocker)
};

#endif // QT_NO_THREAD

#endif // QMUTEX_H
