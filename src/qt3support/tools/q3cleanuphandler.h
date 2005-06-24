/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#ifndef Q3CLEANUPHANDLER_H
#define Q3CLEANUPHANDLER_H

#include <QtCore/qlist.h>

template<class T>
class Q3CleanupHandler
{
    QListData p;
public:
    inline Q3CleanupHandler()
    { p.d = 0; }
    ~Q3CleanupHandler()
    {
        if (p.d) {
            for (int i = 0; i < p.size(); ++i) {
                T** t = static_cast<T**>(*p.at(i));
                delete *t;
                *t = 0;
            }
            qFree(p.d);
            p.d = 0;
        }
    }

    T* add(T **object)
    {
        if (!p.d) {
            p.d = &QListData::shared_null;
            p.d->ref.ref();
            p.detach();
        }
        *p.prepend() =  object;
        return *object;
    }
    void remove(T **object)
    {
        if (p.d)
            for (int i = 0; i < p.size(); ++i)
                if (*p.at(i) == object)
                    p.remove(i--);
    }
};

template<class T>
class Q3SingleCleanupHandler
{
    T **object;
public:
    inline Q3SingleCleanupHandler()
    : object(0) {}
    inline ~Q3SingleCleanupHandler()
    { if (object) { delete *object; *object = 0; } }
    inline T* set(T **o)
    { object = o; return *object; }
    inline void reset() { object = 0; }
};

#endif //Q3CLEANUPHANDLER_H
