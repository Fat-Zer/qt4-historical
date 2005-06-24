/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
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

#ifndef DATABASEINFO_H
#define DATABASEINFO_H

#include "treewalker.h"
#include <qstringlist.h>
#include <qmap.h>

class Driver;

class DatabaseInfo : public TreeWalker
{
public:
    DatabaseInfo(Driver *driver);

    void acceptUI(DomUI *node);
    void acceptWidget(DomWidget *node);

    inline QStringList connections() const
    { return m_connections; }

    inline QStringList cursors(const QString &connection) const
    { return m_cursors.value(connection); }

    inline QStringList fields(const QString &connection) const
    { return m_fields.value(connection); }

private:
    Driver *driver;
    QStringList m_connections;
    QMap<QString, QStringList> m_cursors;
    QMap<QString, QStringList> m_fields;
};

#endif // DATABASEINFO_H
