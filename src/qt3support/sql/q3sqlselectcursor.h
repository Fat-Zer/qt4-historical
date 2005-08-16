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

#ifndef Q3SQLSELECTCURSOR_H
#define Q3SQLSELECTCURSOR_H

#include "Qt3Support/q3sqlcursor.h"

#ifndef QT_NO_SQL

class Q3SqlSelectCursorPrivate;

class Q_COMPAT_EXPORT Q3SqlSelectCursor : public Q3SqlCursor
{
public:
    Q3SqlSelectCursor(const QString& query = QString(), QSqlDatabase db = QSqlDatabase());
    Q3SqlSelectCursor(const Q3SqlSelectCursor& other);
    ~Q3SqlSelectCursor();
    bool exec(const QString& query);
    bool select() { return Q3SqlCursor::select(); }

protected:
    QSqlIndex primaryIndex(bool = true) const { return QSqlIndex(); }
    QSqlIndex index(const QStringList&) const { return QSqlIndex(); }
    QSqlIndex index(const QString&) const { return QSqlIndex(); }
    QSqlIndex index(const char*) const { return QSqlIndex(); }
    void setPrimaryIndex(const QSqlIndex&) {}
    void append(const Q3SqlFieldInfo&) {}
    void insert(int, const Q3SqlFieldInfo&) {}
    void remove(int) {}
    void clear() {}
    void setGenerated(const QString&, bool) {}
    void setGenerated(int, bool) {}
    QSqlRecord*        editBuffer(bool = false) { return 0; }
    QSqlRecord*        primeInsert() { return 0; }
    QSqlRecord*        primeUpdate() { return 0; }
    QSqlRecord*        primeDelete() { return 0; }
    int        insert(bool = true) { return 0; }
    int        update(bool = true) { return 0; }
    int        del(bool = true) { return 0; }
    void setMode(int) {}

    void setSort(const QSqlIndex&) {}
    QSqlIndex sort() const { return QSqlIndex(); }
    void setFilter(const QString&) {}
    QString filter() const { return QString(); }
    void setName(const QString&, bool = true) {}
    QString name() const { return QString(); }
    QString toString(const QString& = QString(), const QString& = ",") const { return QString(); }
    bool select(const QString &, const QSqlIndex& = QSqlIndex());

private:
    void populateCursor();

    Q3SqlSelectCursorPrivate * d;
};

#endif // QT_NO_SQL

#endif // Q3SQLSELECTCURSOR_H
