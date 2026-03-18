/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QREADWRITELOCK_P_H
#define QREADWRITELOCK_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of qreadwritelock_unix.cpp and qreadwritelock_win.cpp.  This header file may change
// from version to version without notice, or even be removed.
//
// We mean it.
//

#ifdef Q_OS_UNIX
struct QReadWriteLockPrivate
{
    QAtomic accessCount;
    QAtomic waitingWriters;
    QAtomic waitingReaders;
    pthread_mutex_t mutex;
    pthread_cond_t readerWait;
    pthread_cond_t writerWait;

};
#endif

#ifdef Q_OS_WIN32
struct QReadWriteLockPrivate
{
    volatile int accessCount;
    QAtomic waitingWriters;
    QAtomic waitingReaders;
    HANDLE readerWait;
    HANDLE writerWait;
};
#endif

#endif // QREADWRITELOCK_P_H
