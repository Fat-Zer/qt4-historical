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

#include "qapplication.h"

#ifndef QT_NO_SOUND

#include "qsound.h"
#include "qpaintdevice.h"
#include "qwsdisplay_qws.h"
#include "qsound_p.h"

class QAuServerQWS : public QAuServer {
public:
    QAuServerQWS(QObject* parent);

    void play(const QString& filename)
    {
        QPaintDevice::qwsDisplay()->playSoundFile(filename);
    }
    void play(QSound* s)
    {
        QPaintDevice::qwsDisplay()->playSoundFile(s->fileName());
    }
    void stop(QSound*)
    {
        // ####
    }

    bool okay() { return true; }
};

QAuServerQWS::QAuServerQWS(QObject* parent) :
    QAuServer(parent)
{
}


QAuServer* qt_new_audio_server()
{
    return new QAuServerQWS(qApp);
}

#endif // QT_NO_SOUND
