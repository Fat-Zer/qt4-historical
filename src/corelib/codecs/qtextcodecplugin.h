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

#ifndef QTEXTCODECPLUGIN_H
#define QTEXTCODECPLUGIN_H

#include "QtCore/qplugin.h"
#include "QtCore/qfactoryinterface.h"

#include <QtCore/qlist.h>
#include <QtCore/qbytearray.h>

class QTextCodec;

struct Q_CORE_EXPORT QTextCodecFactoryInterface : public QFactoryInterface
{
    virtual QTextCodec *create(const QString &key) = 0;
};

#define QTextCodecFactoryInterface_iid "com.trolltech.Qt.QTextCodecFactoryInterface"

Q_DECLARE_INTERFACE(QTextCodecFactoryInterface, QTextCodecFactoryInterface_iid)

class Q_CORE_EXPORT QTextCodecPlugin : public QObject, public QTextCodecFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(QTextCodecFactoryInterface:QFactoryInterface)
public:
    explicit QTextCodecPlugin(QObject *parent = 0);
    ~QTextCodecPlugin();

    virtual QList<QByteArray> names() const = 0;
    virtual QList<QByteArray> aliases() const = 0;
    virtual QTextCodec *createForName(const QByteArray &name) = 0;

    virtual QList<int> mibEnums() const = 0;
    virtual QTextCodec *createForMib(int mib) = 0;

private:
    QStringList keys() const;
    QTextCodec *create(const QString &name);
};

#endif // QTEXTCODECPLUGIN_H
