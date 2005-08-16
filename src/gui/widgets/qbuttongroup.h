/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QBUTTONGROUP_H
#define QBUTTONGROUP_H

#include "QtCore/qobject.h"

class QAbstractButton;
class QAbstractButtonPrivate;
class QButtonGroupPrivate;

class Q_GUI_EXPORT QButtonGroup : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool exclusive READ exclusive WRITE setExclusive)
public:
    explicit QButtonGroup(QObject *parent = 0);
    ~QButtonGroup();

    void setExclusive(bool);
    bool exclusive() const;

    void addButton(QAbstractButton *);
    void removeButton(QAbstractButton *);

    QList<QAbstractButton*> buttons() const;

    QAbstractButton * checkedButton() const;
    // no setter on purpose!

signals:
    void buttonClicked(QAbstractButton *);

#ifdef QT3_SUPPORT
public:
    inline QT3_SUPPORT void insert(QAbstractButton *b) { addButton(b); }
    inline QT3_SUPPORT void remove(QAbstractButton *b) { removeButton(b); }
#endif

private:
    Q_DISABLE_COPY(QButtonGroup)
    Q_DECLARE_PRIVATE(QButtonGroup)
    friend class QAbstractButton;
    friend class QAbstractButtonPrivate;
};

#endif // QBUTTONGROUP_H
