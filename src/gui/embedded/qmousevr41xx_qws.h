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

#ifndef QMOUSEVR41XX_QWS_H
#define QMOUSEVR41XX_QWS_H

#include "QtGui/qmouse_qws.h"

QT_MODULE(Gui)

#ifndef QT_NO_QWS_MOUSE_VR41XX

class QWSVr41xxMouseHandlerPrivate;

class QWSVr41xxMouseHandler : public QWSCalibratedMouseHandler
{
public:
    explicit QWSVr41xxMouseHandler(const QString & = QString(),
                                   const QString & = QString());
    ~QWSVr41xxMouseHandler();

protected:
    QWSVr41xxMouseHandlerPrivate *d;
};

#endif

#endif // QMOUSEVR41XX_QWS_H
