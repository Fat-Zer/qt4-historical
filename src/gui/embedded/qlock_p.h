/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the embedded classes of the Qt Toolkit.
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

#ifndef QLOCK_P_H
#define QLOCK_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  This header file may
// change from version to version without notice, or even be
// removed.
//
// We mean it.
//

#include "qstring.h"

class QLockData;

class QLock
{
public:
    QLock(const QString &filename, char id, bool create = false);
    ~QLock();

    enum Type { Read, Write };

    bool isValid() const;
    void lock(Type type);
    void unlock();
    bool locked() const;

private:
    Type type;
    QLockData *data;
};


// Nice class for ensuring the lock is released.
// Just create one on the stack and the lock is automatically released
// when QLockHandle is destructed.
class QLockHandle
{
public:
    QLockHandle(QLock *l, QLock::Type type) : qlock(l) { qlock->lock(type); }
    ~QLockHandle() { if (locked()) qlock->unlock(); }

    void lock(QLock::Type type) { qlock->lock(type); }
    void unlock() { qlock->unlock(); }
    bool locked() const { return qlock->locked(); }

private:
    QLock *qlock;
};

#endif // QLOCK_P_H
