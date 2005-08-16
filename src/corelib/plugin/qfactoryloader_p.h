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

#ifndef QFACTORYLOADER_P_H
#define QFACTORYLOADER_P_H

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

#include <qobject.h>
#include <qstringlist.h>
#include "qlibrary_p.h"

class QFactoryLoaderPrivate;

class Q_CORE_EXPORT QFactoryLoader : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QFactoryLoader)

public:
    QFactoryLoader(const char *iid,
                   const QStringList &paths = QStringList(),
                   const QString &suffix = QString(),
                   Qt::CaseSensitivity = Qt::CaseSensitive);
    ~QFactoryLoader();

    QStringList keys() const;
    QObject *instance(const QString &key) const;

};

#endif // QFACTORYLOADER_P_H
