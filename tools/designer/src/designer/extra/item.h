/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#ifndef ITEM_H
#define ITEM_H

#include <QtCore/QString>
#include <QtGui/QPixmap>

class Item
{
public:
    enum ItemType { BusinessCard, Weapon, Armor };
    Item(ItemType type, const QString &pixName, const QString &name, const QString &description)
        : m_name(name), m_description(description), m_type(type), m_pic(pixName) {}
    virtual ~Item() {}
    inline QString name() const { return m_name; }
    inline QString description() const { return m_description; }
    inline ItemType type() const { return m_type; }
    inline QString pixmapName() const { return m_pic; }

private:
    QString m_name;
    QString m_description;
    ItemType m_type;
    QString m_pic;
};

class BusinessCard : public Item
{
public:
    BusinessCard(const QString &name, const QString &description, const QString &bigpic)
        : Item(Item::BusinessCard, QLatin1String(":/qthack/images/bcard.png"),
               name, description), m_bigPic(bigpic)
    {}
    inline QString bigPicture() const { return m_bigPic; }
private:
    QString m_bigPic;
};
#endif
