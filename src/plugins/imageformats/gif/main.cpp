/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the plugins of the Qt Toolkit.
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

#ifndef QT_CLEAN_NAMESPACE
#define QT_CLEAN_NAMESPACE
#endif
#include <qimageiohandler.h>
#include <qstringlist.h>

#ifndef QT_NO_IMAGEFORMATPLUGIN

#ifdef QT_NO_IMAGEFORMAT_GIF
#undef QT_NO_IMAGEFORMAT_GIF
#endif
#include "qgifhandler.h"

class QGifPlugin : public QImageIOPlugin
{
public:
    QGifPlugin();
    ~QGifPlugin();

    QStringList keys() const;
    Capabilities capabilities(QIODevice *device, const QByteArray &format) const;
    QImageIOHandler *create(QIODevice *device, const QByteArray &format = QByteArray()) const;
};

QGifPlugin::QGifPlugin()
{
}

QGifPlugin::~QGifPlugin()
{
}

QStringList QGifPlugin::keys() const
{
    return QStringList() << "gif";
}

QImageIOPlugin::Capabilities QGifPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
    if (format == "gif" || (device && device->isReadable() && QGifHandler::canRead(device)))
        return Capabilities(CanRead);
    return 0;
}

QImageIOHandler *QGifPlugin::create(QIODevice *device, const QByteArray &format) const
{
    QImageIOHandler *handler = new QGifHandler;
    handler->setDevice(device);
    handler->setFormat(format);
    return handler;
}

Q_EXPORT_PLUGIN(QGifPlugin)

#endif // QT_NO_IMAGEFORMATPLUGIN
