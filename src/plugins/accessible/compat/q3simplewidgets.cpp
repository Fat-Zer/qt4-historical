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

#include "q3simplewidgets.h"

#include <q3groupbox.h>
#include <qlabel.h>

QString Q_GUI_EXPORT qt_accStripAmp(const QString &text);

Q3AccessibleDisplay::Q3AccessibleDisplay(QWidget *w, Role role)
: QAccessibleWidget(w, role)
{
}

/*! \reimp */
QAccessible::Role Q3AccessibleDisplay::role(int child) const
{
    QLabel *l = qobject_cast<QLabel*>(object());
    if (l) {
        if (l->pixmap() || l->picture())
            return Graphic;
        if (l->picture())
            return Graphic;
        if (l->movie())
            return Animation;
    }
    return QAccessibleWidget::role(child);
}

/*! \reimp */
QString Q3AccessibleDisplay::text(Text t, int child) const
{
    QString str;
    switch (t) {
    case Name:
        if (qobject_cast<QLabel*>(object())) {
            str = qobject_cast<QLabel*>(object())->text();
        } else if (qobject_cast<Q3GroupBox*>(object())) {
            str = qobject_cast<Q3GroupBox*>(object())->title();
        }
        break;
    default:
        break;
    }
    if (str.isEmpty())
        str = QAccessibleWidget::text(t, child);;
    return qt_accStripAmp(str);
}

/*! \reimp */
QAccessible::Relation Q3AccessibleDisplay::relationTo(int child, const QAccessibleInterface *other,
                                                      int otherChild) const
{
    Relation relation = QAccessibleWidget::relationTo(child, other, otherChild);
    if (child || otherChild)
        return relation;

    QObject *o = other->object();
    QLabel *label = qobject_cast<QLabel*>(object());
    Q3GroupBox *groupbox = qobject_cast<Q3GroupBox*>(object());
    if (label) {
        if (o == label->buddy())
            relation |= Label;
    } else if (groupbox && !groupbox->title().isEmpty()) {
        if (groupbox->children().contains(o))
            relation |= Label;
    }
    return relation;
}

/*! \reimp */
int Q3AccessibleDisplay::navigate(RelationFlag rel, int entry, QAccessibleInterface **target) const
{
    *target = 0;
    if (rel == Labelled) {
        QObject *targetObject = 0;
        QLabel *label = qobject_cast<QLabel*>(object());
        Q3GroupBox *groupbox = qobject_cast<Q3GroupBox*>(object());
        if (label) {
            if (entry == 1)
                targetObject = label->buddy();
        } else if (groupbox && !groupbox->title().isEmpty()) {
            rel = Child;
        }
        *target = QAccessible::queryAccessibleInterface(targetObject);
        if (*target)
            return 0;
    }
    return QAccessibleWidget::navigate(rel, entry, target);
}

