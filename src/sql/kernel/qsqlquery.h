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

#ifndef QSQLQUERY_H
#define QSQLQUERY_H

#include "QtSql/qsql.h"
#include "QtSql/qsqldatabase.h"
#include "QtCore/qstring.h"

class QVariant;
class QSqlDriver;
class QSqlError;
class QSqlResult;
class QSqlRecord;
template <class Key, class T> class QMap;

class QSqlQueryPrivate;

class Q_SQL_EXPORT QSqlQuery
{
public:
    QSqlQuery(QSqlResult *r);
    QSqlQuery(const QString& query = QString(), QSqlDatabase db = QSqlDatabase());
    explicit QSqlQuery(QSqlDatabase db);
    QSqlQuery(const QSqlQuery& other);
    QSqlQuery& operator=(const QSqlQuery& other);
    ~QSqlQuery();

    bool isValid() const;
    bool isActive() const;
    bool isNull(int field) const;
    int at() const;
    QString lastQuery() const;
    int numRowsAffected() const;
    QSqlError lastError() const;
    bool isSelect() const;
    int size() const;
    const QSqlDriver* driver() const;
    const QSqlResult* result() const;
    bool isForwardOnly() const;
    QSqlRecord record() const;

    void setForwardOnly(bool forward);
    bool exec(const QString& query);
    QVariant value(int i) const;

    bool seek(int i, bool relative = false);
    bool next();
    bool previous();
#ifdef QT3_SUPPORT
    inline QT3_SUPPORT bool prev() { return previous(); }
#endif
    bool first();
    bool last();

    void clear();

    // prepared query support
    bool exec();
    bool prepare(const QString& query);
    void bindValue(const QString& placeholder, const QVariant& val,
                   QSql::ParamType type = QSql::In);
    void bindValue(int pos, const QVariant& val, QSql::ParamType type = QSql::In);
    void addBindValue(const QVariant& val, QSql::ParamType type = QSql::In);
    QVariant boundValue(const QString& placeholder) const;
    QVariant boundValue(int pos) const;
    QMap<QString, QVariant> boundValues() const;
    QString executedQuery() const;
    QVariant lastInsertId() const;

private:
    QSqlQueryPrivate* d;
};

#endif // QSQLQUERY_H
