/****************************************************************************
**
** Copyright (C) 2005-2006 Trolltech ASA. All rights reserved.
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

#include <QtGui>

#include "treemodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel model(file.readAll());
    file.close();

    QTreeView unsortedView;
    unsortedView.setModel(&model);
    unsortedView.setWindowTitle(QObject::tr("Unsorted Data"));
    unsortedView.show();

    QSortFilterProxyModel sortingModel;
    sortingModel.setSourceModel(&model);

    QTreeView sortedView;
    sortedView.setModel(&sortingModel);
    sortedView.setWindowTitle(QObject::tr("Sorted Data"));
    sortedView.header()->setSortIndicator(1, Qt::AscendingOrder);
    sortedView.header()->setSortIndicatorShown(true);
    sortedView.header()->setClickable(true);
    sortedView.show();

    return app.exec();
}
