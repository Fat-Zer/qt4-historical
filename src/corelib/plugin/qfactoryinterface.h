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

#ifndef QFACTORYINTERFACE_H
#define QFACTORYINTERFACE_H

#include "QtCore/qobject.h"
#include "QtCore/qstringlist.h"

QT_MODULE(Core)

struct QFactoryInterface
{
    virtual ~QFactoryInterface() {}
    virtual QStringList keys() const = 0;
};

Q_DECLARE_INTERFACE(QFactoryInterface, "com.trolltech.Qt.QFactoryInterface")

#endif // QFACTORYINTERFACE_H
