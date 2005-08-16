/****************************************************************************
**
** Copyright (C) 2007-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <QtCore/QObject>
#include <QtScript/QScriptable>

class ListWidgetItemPrototype : public QObject, public QScriptable
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
public:
    ListWidgetItemPrototype(QObject *parent = 0);

    QString text() const;
    void setText(const QString &text);

public Q_SLOTS:
    QString toString() const;
};

class ListWidgetPrototype : public QObject, public QScriptable
{
    Q_OBJECT
public:
    ListWidgetPrototype(QObject *parent = 0);

public Q_SLOTS:
    void addItem(const QString &text);
    void addItems(const QStringList &texts);
    void setBackgroundColor(const QString &colorName);
};

#endif
