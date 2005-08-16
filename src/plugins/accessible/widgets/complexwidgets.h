/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the accessibility module of the Qt Toolkit.
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

#ifndef COMPLEXWIDGETS_H
#define COMPLEXWIDGETS_H

#include <qaccessiblewidget.h>

class QAbstractButton;
class QHeaderView;
class QTabBar;
class QComboBox;
class QTitleBar;

class QAccessibleHeader : public QAccessibleWidget
{
public:
    explicit QAccessibleHeader(QWidget *w);

    int childCount() const;

    QRect rect(int child) const;
    QString text(Text t, int child) const;
    Role role(int child) const;
    State state(int child) const;

protected:
    QHeaderView *header() const;
};

class QAccessibleTabBar : public QAccessibleWidget
{
public:
    explicit QAccessibleTabBar(QWidget *w);

    int childCount() const;

    QRect rect(int child) const;
    QString text(Text t, int child) const;
    Role role(int child) const;
    State state(int child) const;

    bool doAction(int action, int child, const QVariantList &params);
    bool setSelected(int child, bool on, bool extend);
    QVector<int> selection() const;

protected:
    QTabBar *tabBar() const;

private:
    QAbstractButton *button(int child) const;
};

class QAccessibleComboBox : public QAccessibleWidget
{
public:
    explicit QAccessibleComboBox(QWidget *w);

    enum ComboBoxElements {
        ComboBoxSelf        = 0,
        CurrentText,
        OpenList,
        PopupList
    };

    int childCount() const;
    int childAt(int x, int y) const;
    int indexOfChild(const QAccessibleInterface *child) const;
    int navigate(RelationFlag rel, int entry, QAccessibleInterface **target) const;

    QString text(Text t, int child) const;
    QRect rect(int child) const;
    Role role(int child) const;
    State state(int child) const;

    bool doAction(int action, int child, const QVariantList &params);

protected:
    QComboBox *comboBox() const;
};

#endif // COMPLEXWIDGETS_H
