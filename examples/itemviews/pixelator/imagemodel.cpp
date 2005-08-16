/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
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

#include "imagemodel.h"

ImageModel::ImageModel(const QImage &image, QObject *parent)
    : QAbstractTableModel(parent)
{
    modelImage = QImage(image);
}

int ImageModel::rowCount(const QModelIndex & /* parent */) const
{
    return modelImage.height();
}

int ImageModel::columnCount(const QModelIndex & /* parent */) const
{
    return modelImage.width();
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    else if (role != Qt::DisplayRole)
        return QVariant();

    return qGray(modelImage.pixel(index.column(), index.row()));
}
