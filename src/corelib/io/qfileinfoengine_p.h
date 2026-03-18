/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QFILEINFOENGINE_P_H
#define QFILEINFOENGINE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qplatformdefs.h>

class QFileInfoEngine;
class QFileInfoEnginePrivate
{
protected:
    Q_DECLARE_PUBLIC(QFileInfoEngine)
    QFileInfoEngine *q_ptr;
protected:
    inline QFileInfoEnginePrivate() : q_ptr(0) { }
    ~QFileInfoEnginePrivate() { q_ptr = 0; }
};


class QFSFileInfoEngine;
class QFSFileInfoEnginePrivate : public QFileInfoEnginePrivate
{
    Q_DECLARE_PUBLIC(QFSFileInfoEngine)
protected:
    QFSFileInfoEnginePrivate();

    void init();
    void slashify();
private:
    QString file;

    mutable uint could_stat : 1;
    mutable uint tried_stat : 1;
    mutable QT_STATBUF st;
    bool doStat() const;

#if defined(Q_OS_WIN32)
    uint getPermissions() const;
    QString getLink() const;
#endif
};

#endif // QFILEINFOENGINE_P_H
