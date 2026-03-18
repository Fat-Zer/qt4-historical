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

#ifndef QGFXVNC_QWS_H
#define QGFXVNC_QWS_H

#define VNCSCREEN_BASE QLinuxFbScreen
#include "QtGui/qscreenlinuxfb_qws.h"

QT_MODULE(Gui)

#ifndef QT_NO_QWS_VNC

class QVNCServer;
class QVNCHeader;
class QSharedMemory;

class QVNCScreen : public VNCSCREEN_BASE {
public:
    explicit QVNCScreen(int display_id);
    virtual ~QVNCScreen();
    virtual bool initDevice();
    virtual bool connect(const QString &displaySpec);
    virtual void disconnect();
    virtual int initCursor(void*, bool);
    virtual void shutdownDevice();
//    virtual QGfx * createGfx(unsigned char *,int,int,int,int);
    virtual void save();
    virtual void restore();
    virtual void setMode(int nw,int nh,int nd);

    virtual void setDirty(const QRect& r);

    bool success;
    QVNCServer *vncServer;
    unsigned char *shmrgn;
    QSharedMemory *shm;
    QVNCHeader *hdr;
    bool virtualBuffer;
};

#endif // QT_NO_QWS_VNC

#endif // QGFXVNC_QWS_H
