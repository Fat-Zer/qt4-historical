/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the gui module of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QSOUND_H
#define QSOUND_H

#include "QtCore/qobject.h"

#ifndef QT_NO_SOUND

class QSoundPrivate;

class Q_GUI_EXPORT QSound : public QObject
{
    Q_OBJECT

public:
    static bool isAvailable();
    static void play(const QString& filename);

    explicit QSound(const QString& filename, QObject* parent = 0);
    ~QSound();

    int loops() const;
    int loopsRemaining() const;
    void setLoops(int);
    QString fileName() const;

    bool isFinished() const;

public slots:
    void play();
    void stop();

public:
#ifdef QT3_SUPPORT
    QT3_SUPPORT_CONSTRUCTOR QSound(const QString& filename, QObject* parent, const char* name);
    static inline QT3_SUPPORT bool available() { return isAvailable(); }
#endif
private:
    Q_DECLARE_PRIVATE(QSound)
    friend class QAuServer;
};

#endif // QT_NO_SOUND

#endif // QSOUND_H
