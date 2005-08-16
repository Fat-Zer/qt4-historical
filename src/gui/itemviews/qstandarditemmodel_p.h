/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QSTANDARDITEMMODEL_P_H
#define QSTANDARDITEMMODEL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <private/qabstractitemmodel_p.h>

#ifndef QT_NO_STANDARDITEMMODEL

class  QStdModelItem {
public:
    QStdModelItem() {};
    QVariant value(int role) const
        {
            for (int i=0; i<roles.count(); ++i)
                if (roles.at(i).first == role)
                    return roles.at(i).second;
            return QVariant();
        }
    void setValue(int role, QVariant value)
        {
            for (int i=0; i<roles.count(); ++i)
                if (roles.at(i).first == role) {
                    roles[i].second = value;
                    return;
                }
            roles.append(QPair<int, QVariant>(role, value));
            return;
        }

    QVector<QPair<int, QVariant> > roles;
};

class QStdModelRow {
public:
    explicit QStdModelRow(QStdModelRow *parent) : p(parent), childrenColumns(0) {}
    ~QStdModelRow()
    {
        qDeleteAll(items);
        qDeleteAll(childrenRows);
    }

    QStdModelRow *p;
    QVector<QStdModelItem*> items;
    int childrenColumns;
    QVector<QStdModelRow*> childrenRows;
};

class QStandardItemModelPrivate : public QAbstractItemModelPrivate
{

    Q_DECLARE_PUBLIC(QStandardItemModel)

public:
    QStandardItemModelPrivate(int rows, int columns) : topLevelRows(rows), topLevelColumns(columns) {}
    virtual ~QStandardItemModelPrivate();

    QStdModelRow *containedRow(const QModelIndex &index, bool createIfMissing) const;
    void clear();

    QVector<QStdModelRow*> topLevelRows;
    QVector<QStdModelItem*> horizontalHeader, verticalHeader;
    int topLevelColumns;
};

#endif // QT_NO_STANDARDITEMMODEL
#endif // QSTANDARDITEMMODEL_P_H
