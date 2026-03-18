/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QKBDSL5000_QWS_H
#define QKBDSL5000_QWS_H

#include "QtGui/qkbdtty_qws.h"

QT_MODULE(Gui)

#ifdef QT_QWS_KBD_SL5000

class QWSSL5000KbPrivate;

class QWSSL5000KeyboardHandler : public QWSTtyKeyboardHandler
{
public:
    explicit QWSSL5000KeyboardHandler(const QString&);
    virtual ~QWSSL5000KeyboardHandler();

    virtual void doKey(uchar scancode);
    virtual const QWSKeyMap *keyMap() const;

private:
    bool meta;
    bool fn;
    bool numLock;
    QWSSL5000KbPrivate *d;
};

#endif // QT_NO_QWS_KBD_SL5000

#endif // QKBDSL5000_QWS_H
