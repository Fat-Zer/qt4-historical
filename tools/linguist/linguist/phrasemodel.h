/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Linguist of the Qt Toolkit.
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

#ifndef PHRASEMODEL_H
#define PHRASEMODEL_H

#include "phrase.h"

#include <qlist.h>
#include <qabstractitemmodel.h>

class PhraseModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    PhraseModel(QObject *parent = 0)
        : QAbstractTableModel(parent), sortColumn(-1) {}

    void removePhrases();
    QList<Phrase> phraseList() const {return plist;}

    QModelIndex addPhrase(Phrase p);
    void removePhrase(const QModelIndex &index);

    Phrase phrase(const QModelIndex &index) const;
    void setPhrase(const QModelIndex &indx, Phrase ph);
    QModelIndex index(const Phrase phr) const;

    static bool compare(const Phrase &left, const Phrase &right);
    bool sortParameters(Qt::SortOrder &so, int &sc) const;
    void resort();

    // from qabstracttablemodel
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

private:
    Qt::SortOrder sortOrder;
    int sortColumn;

    QList<Phrase> plist;
};

#endif //PHRASEMODEL_H
