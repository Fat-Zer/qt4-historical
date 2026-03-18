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

#ifndef Q3SQLPROPERTYMAP_H
#define Q3SQLPROPERTYMAP_H

#include "QtCore/qvariant.h"
#include "QtCore/qstring.h"

QT_MODULE(Qt3Support)

#ifndef QT_NO_SQL_FORM

class QWidget;
class Q3SqlPropertyMapPrivate;

class Q_COMPAT_EXPORT Q3SqlPropertyMap
{
public:
    Q3SqlPropertyMap();
    virtual ~Q3SqlPropertyMap();

    QVariant      property(QWidget * widget);
    virtual void  setProperty(QWidget * widget, const QVariant & value);

    void insert(const QString & classname, const QString & property);
    void remove(const QString & classname);

    static Q3SqlPropertyMap * defaultMap();
    static void installDefaultMap(Q3SqlPropertyMap * map);

private:
    Q_DISABLE_COPY(Q3SqlPropertyMap)

    Q3SqlPropertyMapPrivate* d;
};

#endif // QT_NO_SQL_FORM

#endif // Q3SQLPROPERTYMAP_H
