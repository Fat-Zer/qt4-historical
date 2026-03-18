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

#ifndef QMOUSELINUXTP_QWS_H
#define QMOUSELINUXTP_QWS_H

#include "QtGui/qmouse_qws.h"

QT_MODULE(Gui)

#ifndef QT_NO_QWS_MOUSE_LINUXTP

class QWSLinuxTPMouseHandlerPrivate;

class QWSLinuxTPMouseHandler : public QWSCalibratedMouseHandler
{
public:
    explicit QWSLinuxTPMouseHandler(const QString & = QString(),
                                    const QString & = QString());
    ~QWSLinuxTPMouseHandler();

    void suspend();
    void resume();
protected:
    QWSLinuxTPMouseHandlerPrivate *d;
};

#endif

#endif // QMOUSELINUXTP_QWS_H
