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

#ifndef QSCREENVFB_QWS_H
#define QSCREENVFB_QWS_H

#include "QtGui/qscreen_qws.h"

#ifndef QT_NO_QWS_QVFB

#include "QtGui/qvfbhdr.h"

QT_MODULE(Gui)

class QVFbMouseHandler;
class QVFbKeyboardHandler;

class QVFbScreen : public QScreen
{
public:
    explicit QVFbScreen(int display_id);
    virtual ~QVFbScreen();
    virtual bool initDevice();
    virtual bool connect(const QString &displaySpec);
    virtual void disconnect();
    virtual int initCursor(void*, bool);
    virtual void shutdownDevice();
    virtual void save();
    virtual void restore();
    virtual void setMode(int nw,int nh,int nd);

    virtual void setDirty(const QRect& r)
        { hdr->dirty = true; hdr->update = hdr->update.unite(r); }

    bool success;
    unsigned char *shmrgn;
    QVFbHeader *hdr;
    QVFbMouseHandler *mouseHandler;
    QVFbKeyboardHandler *keyboardHandler;
};

#endif // QT_NO_QWS_QVFB

#endif // QSCREENVFB_QWS_H
