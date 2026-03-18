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

#ifndef Q3TEXTVIEW_H
#define Q3TEXTVIEW_H

#include "Qt3Support/q3textedit.h"

QT_MODULE(Qt3SupportLight)

#ifndef QT_NO_TEXTVIEW

class Q_COMPAT_EXPORT Q3TextView : public Q3TextEdit
{
    Q_OBJECT

public:
    Q3TextView(const QString& text, const QString& context = QString(),
               QWidget* parent=0, const char* name=0);
    Q3TextView(QWidget* parent=0, const char* name=0);

    virtual ~Q3TextView();

private:
    Q_DISABLE_COPY(Q3TextView)
};

#endif //QT_NO_TEXTVIEW
#endif //QTEXTVIEW_H
