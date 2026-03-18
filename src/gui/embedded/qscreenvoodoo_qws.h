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

#ifndef QGFXVOODOO_QWS_H
#define QGFXVOODOO_QWS_H

#include "QtGui/qscreenlinuxfb_qws.h"

QT_MODULE(Gui)

#ifndef QT_NO_QWS_VOODOO

class QVoodooScreen : public QLinuxFbScreen
{
public:
    explicit QVoodooScreen(int display_id);
    virtual ~QVoodooScreen();

    virtual bool connect(const QString &spec);
    virtual bool initDevice();
    virtual void shutdownDevice();
    virtual int initCursor(void *,bool);
    virtual bool useOffscreen();

    virtual QGfx * createGfx(unsigned char *,int,int,int,int);

    unsigned char * voodoo_regbase;
};

#endif // QT_NO_QWS_VOODOO

#endif // QGFXVOODOO_QWS_H
