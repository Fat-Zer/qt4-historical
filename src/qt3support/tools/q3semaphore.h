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

#ifndef Q3SEMAPHORE_H
#define Q3SEMAPHORE_H

#include "QtCore/qglobal.h"

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
