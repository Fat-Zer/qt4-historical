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

#ifndef QACCESSIBLEWIDGET_H
#define QACCESSIBLEWIDGET_H

#include "QtGui/qaccessibleobject.h"

#ifndef QT_NO_ACCESSIBILITY

class QAccessibleWidgetPrivate;

class Q_GUI_EXPORT QAccessibleWidget : public QAccessibleObject
{
public:
    explicit QAccessibleWidget(QWidget *o, Role r = Client, const QString& name = QString());

    int childCount() const;
    int indexOfChild(const QAccessibleInterface *child) const;
    Relation relationTo(int child, const QAccessibleInterface *other, int otherChild) const;

    int childAt(int x, int y) const;
    QRect rect(int child) const;
    int navigate(RelationFlag rel, int entry, QAccessibleInterface **target) const;

    QString text(Text t, int child) const;
    Role role(int child) const;
    State state(int child) const;

    QString actionText(int action, Text t, int child) const;
    bool doAction(int action, int child, const QVariantList &params);

protected:
    ~QAccessibleWidget();
    QWidget *widget() const;
    QObject *parentObject() const;

    void addControllingSignal(const QString &signal);
    void setValue(const QString &value);
    void setDescription(const QString &desc);
    void setHelp(const QString &help);
    void setAccelerator(const QString &accel);

private:
    QAccessibleWidgetPrivate *d;
};

#endif //QT_NO_ACCESSIBILITY

#endif //QACCESSIBLEWIDGET_H
