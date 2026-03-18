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

#ifndef Q3SQLEDITORFACTORY_H
#define Q3SQLEDITORFACTORY_H

#include "Qt3Support/q3editorfactory.h"

QT_MODULE(Qt3Support)

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
