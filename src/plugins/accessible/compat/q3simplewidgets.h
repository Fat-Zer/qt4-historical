/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the accessibility module of the Qt Toolkit.
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

#ifndef Q3SIMPLEWIDGETS_H
#define Q3SIMPLEWIDGETS_H

#include <qaccessiblewidget.h>

class Q3AccessibleDisplay : public QAccessibleWidget
{
public:
    explicit Q3AccessibleDisplay(QWidget *w, Role role = StaticText);

    QString text(Text t, int child) const;
    Role role(int child) const;

    Relation relationTo(int child, const QAccessibleInterface *other, int otherChild) const;
    int navigate(RelationFlag, int entry, QAccessibleInterface **target) const;
};

#endif // Q3SIMPLEWIDGETS_H
