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

#ifndef QGFXMATROX_QWS_H
#define QGFXMATROX_QWS_H

#include "QtGui/qscreenlinuxfb_qws.h"

QT_MODULE(Gui)

#ifndef QT_NO_QWS_MATROX

class QMatroxScreen : public QLinuxFbScreen
{
public:
    explicit QMatroxScreen(int display_id);
    virtual ~QMatroxScreen();

    virtual bool connect(const QString &spec);
    virtual bool initDevice();
    virtual void shutdownDevice();
    virtual bool useOffscreen();
    virtual int initCursor(void*, bool);
    virtual QGfx * createGfx(unsigned char *,int,int,int,int);

protected:
    virtual int pixmapOffsetAlignment();
    virtual int pixmapLinestepAlignment();

private:
    unsigned int src_pixel_offset;
};


#endif // QT_NO_QWS_MATROX

#endif // QGFXMATROX_QWS_H
