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

#ifndef QKBDUSB_QWS_H
#define QKBDUSB_QWS_H

#include "QtGui/qkbdpc101_qws.h"

QT_MODULE(Gui)

#ifndef QT_NO_QWS_KEYBOARD

#ifndef QT_NO_QWS_KBD_USB

class QWSUsbKbPrivate;

class QWSUsbKeyboardHandler : public QWSPC101KeyboardHandler
{
public:
    QWSUsbKeyboardHandler(const QString&);
    virtual ~QWSUsbKeyboardHandler();

private:
    QWSUsbKbPrivate *d;
};

#endif // QT_NO_QWS_KBD_USB

#endif // QT_NO_QWS_KEYBOARD

#endif // QKBDUSB_QWS_H
