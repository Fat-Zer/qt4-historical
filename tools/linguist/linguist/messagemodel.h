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

#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <metatranslator.h>
#include <qabstractitemmodel.h>
#include <qlist.h>

class ContextItem;

class MessageItem
{
public:
    MessageItem(const MetaTranslatorMessage &message,
        const QString &text, const QString &comment, ContextItem *ctxtI);
    inline virtual ~MessageItem() {}

    inline virtual bool danger() const {return d;}

    inline void setTranslation(const QString &translation) {m.setTranslation(translation);}
    void setFinished(bool finished);
    void setDanger(bool danger);

    inline void setContextItem(ContextItem *ctxtI) {cntxtItem = ctxtI;}
    inline ContextItem *contextItem() const {return cntxtItem;}

    inline QString context() const {return m.context();}
    inline QString sourceText() const {return tx;}
    inline QString comment() const {return com;}
    inline QString translation() const {return m.translation();}
    inline bool finished() const {return fini;}
    inline MetaTranslatorMessage message() const {return m;}

private:
    MetaTranslatorMessage m;
    QString tx;
    QString com;
    bool fini;
    bool d;
    ContextItem *cntxtItem;
};

class MessageModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MessageModel(QObject *parent = 0);

    ContextItem *contextItem() {return cntxtItem;}
    void setContextItem(ContextItem *ctxtI);
    void updateItem(QModelIndex indx);

    // from qabstracttablemodel
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

private:
    ContextItem *cntxtItem;
};

#endif //MESSAGEMODEL_H
