/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the core module of the Qt Toolkit.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QBUFFEREDFSFILEENGINE_P_H
#define QBUFFEREDFSFILEENGINE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qplatformdefs.h>
#include <qiodevice.h>

#include "qfileengine.h"
#include <private/qfsfileengine_p.h>

class QBufferedFSFileEnginePrivate;
class QBufferedFSFileEngine : public QFSFileEngine
{
    Q_DECLARE_PRIVATE(QBufferedFSFileEngine)
public:
    QBufferedFSFileEngine();

    enum BufferedFSFileEngineType {
        BufferedFSFileEngine = MaxUser + 1
    };

    Type type() const;
    bool open(int flags);
    bool open(int flags, FILE *fh);
    bool close();
    void flush();
    qint64 at() const;
    bool seek(qint64);
    qint64 read(char *data, qint64 maxlen);
    qint64 write(const char *data, qint64 len);
};

class QBufferedFSFileEnginePrivate : public QFSFileEnginePrivate
{
    Q_DECLARE_PUBLIC(QBufferedFSFileEngine)

public:
    inline QBufferedFSFileEnginePrivate()
    {
        fh = 0;
        lastIOCommand = IOFlushCommand;
    }

    FILE *fh;
    
    enum LastIOCommand
    {
        IOFlushCommand,
        IOReadCommand,
        IOWriteCommand
    };
    LastIOCommand  lastIOCommand;

};

#endif
