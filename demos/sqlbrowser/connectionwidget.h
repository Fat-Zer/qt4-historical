/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <qwidget.h>

class QTreeWidget;
class QTreeWidgetItem;
class QSqlDatabase;
class QMenu;

class ConnectionWidget: public QWidget
{
    Q_OBJECT
public:
    ConnectionWidget(QWidget *parent = 0);
    virtual ~ConnectionWidget();

    QSqlDatabase currentDatabase() const;

signals:
    void tableActivated(const QString &table);

public slots:
    void refresh();
    void on_tree_itemActivated(QTreeWidgetItem *item, int column);

private:
    void setActive(QTreeWidgetItem *);

    QTreeWidget *tree;
    QString activeDb;
};

#endif
