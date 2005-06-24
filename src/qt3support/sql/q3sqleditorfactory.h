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

#ifndef Q3SQLEDITORFACTORY_H
#define Q3SQLEDITORFACTORY_H

#include "Qt3Support/q3editorfactory.h"

#ifndef QT_NO_SQL_EDIT_WIDGETS

class QSqlField;

class Q_COMPAT_EXPORT Q3SqlEditorFactory : public Q3EditorFactory
{
public:
    Q3SqlEditorFactory (QObject * parent = 0);
    ~Q3SqlEditorFactory();
    virtual QWidget * createEditor(QWidget * parent, const QVariant & variant);
    virtual QWidget * createEditor(QWidget * parent, const QSqlField * field);

    static Q3SqlEditorFactory * defaultFactory();
    static void installDefaultFactory(Q3SqlEditorFactory * factory);

private:
    Q_DISABLE_COPY(Q3SqlEditorFactory)
};

#endif // QT_NO_SQL

#endif // Q3SQLEDITORFACTORY_H
