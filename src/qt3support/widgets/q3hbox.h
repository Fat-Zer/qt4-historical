/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt3Support module of the Qt Toolkit.
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

#ifndef Q3HBOX_H
#define Q3HBOX_H

#include "Qt3Support/q3frame.h"

QT_MODULE(Qt3SupportLight)

class QBoxLayout;

class Q_COMPAT_EXPORT Q3HBox : public Q3Frame
{
    Q_OBJECT
public:
    Q3HBox(QWidget* parent=0, const char* name=0, Qt::WFlags f=0);

    void setSpacing(int);
    bool setStretchFactor(QWidget*, int stretch);
    QSize sizeHint() const;

protected:
    Q3HBox(bool horizontal, QWidget* parent, const char* name, Qt::WFlags f = 0);
    void frameChanged();

private:
    Q_DISABLE_COPY(Q3HBox)
};


#endif // Q3HBOX_H
