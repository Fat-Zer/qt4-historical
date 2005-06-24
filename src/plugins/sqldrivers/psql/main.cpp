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

#include <qsqldriverplugin.h>
#include <qstringlist.h>
#include "../../../sql/drivers/psql/qsql_psql.h"

class QPSQLDriverPlugin : public QSqlDriverPlugin
{
public:
    QPSQLDriverPlugin();

    QSqlDriver* create(const QString &);
    QStringList keys() const;
};

QPSQLDriverPlugin::QPSQLDriverPlugin()
    : QSqlDriverPlugin()
{
}

QSqlDriver* QPSQLDriverPlugin::create(const QString &name)
{
    if (name == QLatin1String("QPSQL") || name == QLatin1String("QPSQL7")) {
        QPSQLDriver* driver = new QPSQLDriver();
        return driver;
    }
    return 0;
}

QStringList QPSQLDriverPlugin::keys() const
{
    QStringList l;
    l.append(QLatin1String("QPSQL7"));
    l.append(QLatin1String("QPSQL"));
    return l;
}

Q_EXPORT_PLUGIN(QPSQLDriverPlugin)
