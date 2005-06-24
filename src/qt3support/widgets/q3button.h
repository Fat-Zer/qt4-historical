/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#ifndef Q3BUTTON_H
#define Q3BUTTON_H

#include "QtGui/qabstractbutton.h"

class Q_COMPAT_EXPORT Q3Button : public QAbstractButton
{
    Q_OBJECT
public:
    Q3Button( QWidget* parent=0, const char* name=0, Qt::WFlags f=0 );
    ~Q3Button();

protected:
    virtual void drawButton( QPainter * );
    virtual void drawButtonLabel( QPainter * );
    void	paintEvent( QPaintEvent * );

};

#endif
