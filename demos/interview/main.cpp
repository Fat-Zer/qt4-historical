/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#include <qapplication.h>
#include <qtableview.h>
#include <qtreeview.h>
#include <qlistview.h>
#include <qsplitter.h>
#include <qheaderview.h>
#include "model.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(interview);

    QApplication app(argc, argv);
    QSplitter page;

    QAbstractItemModel *data = new Model(1000, 10, &page);
    QItemSelectionModel *selections = new QItemSelectionModel(data);

    QTableView *table = new QTableView(&page);
    table->setModel(data);
    table->setSelectionModel(selections);
    table->horizontalHeader()->setMovable(true);
    table->verticalHeader()->setMovable(true);

    QTreeView *tree = new QTreeView(&page);
    tree->setModel(data);
    tree->setSelectionModel(selections);
    tree->setUniformRowHeights(true);

    QListView *list = new QListView(&page);
    list->setModel(data);
    list->setSelectionModel(selections);
    list->setViewMode(QListView::IconMode);
    list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    list->setAlternatingRowColors(false);

    page.setWindowIcon(QPixmap(":/images/interview.png"));
    page.show();

    return app.exec();
}
