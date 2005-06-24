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

#include "qglobal.h"

/*!
    \class QSqlRelationalDelegate
    \brief The QSqlRelationalDelegate class provides a delegate that is used to
    display and edit data from a QSqlRelationalTableModel.

    Unlike the default delegate, QSqlRelationalDelegate provides a
    combobox for fields that are foreign keys into other tables. To
    use the class, simply call QAbstractItemView::setItemDelegate()
    on the view with an instance of QSqlRelationalDelegate:

    \quotefromfile sql/relationaltablemodel/relationaltablemodel.cpp
    \skipto QTableView *view = new
    \printuntil setItemDelegate

    The \l{sql/relationaltablemodel} example (shown below)
    illustrates how to use QSqlRelationalDelegate in conjunction with
    QSqlRelationalTableModel to provide tables with foreigh key
    support.

    \image relationaltable.png

    \sa QSqlRelationalTableModel, {Model/View Programming}
*/


/*!
    \fn QSqlRelationalDelegate::QSqlRelationalDelegate(QObject *parent)

    Constructs a QSqlRelationalDelegate object with the given \a
    parent.
*/

/*!
    \fn QSqlRelationalDelegate::~QSqlRelationalDelegate()

    Destroys the QSqlRelationalDelegate object and frees any
    allocated resources.
*/

/*!
    \fn QWidget *QSqlRelationalDelegate::createEditor(QWidget *parent,
                                                      const QStyleOptionViewItem &option,
                                                      const QModelIndex &index) const
    \reimp
*/

/*!
    \fn void QSqlRelationalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
    \reimp
*/

/*!
    \fn void QSqlRelationalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                  const QModelIndex &index) const
    \reimp
*/
