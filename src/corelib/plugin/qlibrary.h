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

#ifndef QLIBRARY_H
#define QLIBRARY_H

#include "QtCore/qobject.h"

class QLibraryPrivate;

class Q_CORE_EXPORT QLibrary : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName)
public:
    explicit QLibrary(QObject *parent = 0);
    explicit QLibrary(const QString& fileName, QObject *parent = 0);
    ~QLibrary();

    void *resolve(const char *symbol);
    static void *resolve(const QString &fileName, const char *symbol);

    bool load();
    bool unload();
    bool isLoaded() const;

    static bool isLibrary(const QString &fileName);

    void setFileName(const QString &fileName);
    QString fileName() const;

#ifdef QT3_SUPPORT
    inline QT3_SUPPORT QString library() const { return fileName(); }
    inline QT3_SUPPORT void setAutoUnload( bool ) {}
#endif
private:
    QLibraryPrivate *d;
    bool did_load;
};

#endif //QLIBRARY_H
