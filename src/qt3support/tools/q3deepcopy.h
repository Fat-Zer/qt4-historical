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

#ifndef Q3DEEPCOPY_H
#define Q3DEEPCOPY_H

#include "QtCore/qglobal.h"

QT_MODULE(Qt3SupportLight)

template <class T>
class Q3DeepCopy
{
public:
    inline Q3DeepCopy()
    {
    }

    inline Q3DeepCopy(const T &t)
	: deepcopy(t)
    {
	deepcopy.detach();
    }

    inline Q3DeepCopy<T> &operator=(const T &t)
    {
	deepcopy = t;
	deepcopy.detach();
	return *this;
    }

    inline operator T ()
    {
	T tmp = deepcopy;
	tmp.detach();
	return tmp;
    }

private:
    T deepcopy;
};

#endif // Q3DEEPCOPY_H
