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

#ifndef QACCESSIBLEMENU_H
#define QACCESSIBLEMENU_H

#include <qaccessiblewidget.h>

class QMenu;
class QMenuBar;

class QAccessibleMenu : public QAccessibleWidget
{
public:
    explicit QAccessibleMenu(QWidget *w);

    int childCount() const;
    int childAt(int x, int y) const;

    QRect rect(int child) const;
    QString text(Text t, int child) const;
    Role role(int child) const;
    State state(int child) const;

    bool doAction(int action, int child, const QVariantList &params);

protected:
    QMenu *menu() const;
};

class QAccessibleMenuBar : public QAccessibleWidget
{
public:
    explicit QAccessibleMenuBar(QWidget *w);

    int childCount() const;
    int childAt(int x, int y) const;

    QRect rect(int child) const;
    QString text(Text t, int child) const;
    Role role(int child) const;
    State state(int child) const;

    bool doAction(int action, int child, const QVariantList &params);

protected:
    QMenuBar *menuBar() const;
};

#endif // QACCESSIBLEMENU_H
