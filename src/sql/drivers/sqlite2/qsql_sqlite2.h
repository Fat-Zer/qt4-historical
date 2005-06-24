/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the sql module of the Qt Toolkit.
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

#ifndef QSQL_SQLITE_H
#define QSQL_SQLITE_H

#include <QtSql/qsqldriver.h>
#include <QtSql/qsqlresult.h>
#include <QtSql/qsqlrecord.h>
#include <QtSql/qsqlindex.h>
#include <QtSql/private/qsqlcachedresult_p.h>

#if defined (Q_OS_WIN32)
# include <QtCore/qt_windows.h>
#endif

class QSQLite2DriverPrivate;
class QSQLite2ResultPrivate;
class QSQLite2Driver;
struct sqlite;

class QSQLite2Result : public QSqlCachedResult
{
    friend class QSQLite2Driver;
    friend class QSQLite2ResultPrivate;
public:
    explicit QSQLite2Result(const QSQLite2Driver* db);
    ~QSQLite2Result();
    QVariant handle() const;

protected:
    bool gotoNext(QSqlCachedResult::ValueCache& row, int idx);
    bool reset (const QString& query);
    int size();
    int numRowsAffected();
    QSqlRecord record() const;

private:
    QSQLite2ResultPrivate* d;
};

class QSQLite2Driver : public QSqlDriver
{
    friend class QSQLite2Result;
public:
    explicit QSQLite2Driver(QObject *parent = 0);
    explicit QSQLite2Driver(sqlite *connection, QObject *parent = 0);
    ~QSQLite2Driver();
    bool hasFeature(DriverFeature f) const;
    bool open(const QString & db,
                   const QString & user,
                   const QString & password,
                   const QString & host,
                   int port,
                   const QString & connOpts);
    bool open(const QString & db,
            const QString & user,
            const QString & password,
            const QString & host,
            int port) { return open (db, user, password, host, port, QString()); }
    void close();
    QSqlResult *createResult() const;
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
    QStringList tables(QSql::TableType) const;

    QSqlRecord record(const QString& tablename) const;
    QSqlIndex primaryIndex(const QString &table) const;
    QVariant handle() const;

private:
    QSQLite2DriverPrivate* d;
};

#endif // QSQL_SQLITE_H
