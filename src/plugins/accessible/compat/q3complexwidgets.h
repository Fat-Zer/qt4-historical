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

#ifndef Q3COMPLEXWIDGETS_H
#define Q3COMPLEXWIDGETS_H

#include <qaccessiblewidget.h>

class Q3Header;
class Q3TitleBar;

class Q3AccessibleHeader : public QAccessibleWidget
{
public:
    explicit Q3AccessibleHeader(QWidget *w);

    int childCount() const;

    QRect rect(int child) const;
    QString text(Text t, int child) const;
    Role role(int child) const;
    State state(int child) const;

protected:
    Q3Header *header() const;
};

class Q3AccessibleTitleBar : public QAccessibleWidget
{
public:
    explicit Q3AccessibleTitleBar(QWidget *w);

    int childCount() const;

    QString text(Text t, int child) const;
    QRect rect(int child) const;
    Role role(int child) const;
    State state(int child) const;

    bool doAction(int action, int child, const QVariantList &params);

protected:
    Q3TitleBar *titleBar() const;
};

#endif // Q3COMPLEXWIDGETS_H
