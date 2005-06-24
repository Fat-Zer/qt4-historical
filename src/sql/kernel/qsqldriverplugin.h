/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the sql module of the Qt Toolkit.
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

#ifndef QSQLDRIVERPLUGIN_H
#define QSQLDRIVERPLUGIN_H

#include "QtCore/qplugin.h"
#include "QtCore/qfactoryinterface.h"

class QSqlDriver;

struct Q_SQL_EXPORT QSqlDriverFactoryInterface : public QFactoryInterface
{
    virtual QSqlDriver *create(const QString &name) = 0;
};

#define QSqlDriverFactoryInterface_iid "com.trolltech.Qt.QSqlDriverFactoryInterface"
Q_DECLARE_INTERFACE(QSqlDriverFactoryInterface, QSqlDriverFactoryInterface_iid)

class Q_SQL_EXPORT QSqlDriverPlugin : public QObject, public QSqlDriverFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(QSqlDriverFactoryInterface:QFactoryInterface)
public:
    explicit QSqlDriverPlugin(QObject *parent = 0);
    ~QSqlDriverPlugin();

    virtual QStringList keys() const = 0;
    virtual QSqlDriver *create(const QString &key) = 0;

};

#endif // QSQLDRIVERPLUGIN_H
