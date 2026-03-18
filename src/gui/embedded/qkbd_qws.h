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

#ifndef QKBD_QWS_H
#define QKBD_QWS_H

#include "QtGui/qapplication.h"

QT_MODULE(Gui)

#ifndef QT_NO_QWS_KEYBOARD

class QWSKbPrivate;

class QWSKeyboardHandler
{
public:
    QWSKeyboardHandler();
    virtual ~QWSKeyboardHandler();

    virtual void processKeyEvent(int unicode, int keycode, Qt::KeyboardModifiers modifiers,
                            bool isPress, bool autoRepeat);

protected:
    int transformDirKey(int key);
    void beginAutoRepeat(int uni, int code, Qt::KeyboardModifiers mod);
    void endAutoRepeat();

private:
    QWSKbPrivate *d;
};

#endif // QT_NO_QWS_KEYBOARD

#endif // QKBD_QWS_H
