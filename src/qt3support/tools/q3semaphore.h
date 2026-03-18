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

#ifndef Q3SEMAPHORE_H
#define Q3SEMAPHORE_H

#include "QtCore/qglobal.h"

QT_MODULE(Qt3SupportLight)

class Q3SemaphorePrivate;

class Q_COMPAT_EXPORT Q3Semaphore
{
public:
    Q3Semaphore(int);
    virtual ~Q3Semaphore();

    int available() const;
    int total() const;

    // postfix operators
    int operator++(int);
    int operator--(int);

    int operator+=(int);
    int operator-=(int);

    bool tryAccess(int);

private:
    Q_DISABLE_COPY(Q3Semaphore)

    Q3SemaphorePrivate *d;
};

#endif // Q3SEMAPHORE_H
