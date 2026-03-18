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

#ifndef QPICTUREFORMATPLUGIN_H
#define QPICTUREFORMATPLUGIN_H

#include "QtCore/qplugin.h"
#include "QtCore/qfactoryinterface.h"

QT_MODULE(Gui)

#if !defined(QT_NO_LIBRARY) && !defined(QT_NO_PICTURE)

class QPicture;
class QImage;
class QString;
class QStringList;

struct Q_GUI_EXPORT QPictureFormatInterface : public QFactoryInterface
{
    virtual bool loadPicture(const QString &format, const QString &filename, QPicture *) = 0;
    virtual bool savePicture(const QString &format, const QString &filename, const QPicture &) = 0;

    virtual bool installIOHandler(const QString &) = 0;
};

#define QPictureFormatInterface_iid "com.trolltech.Qt.QPictureFormatInterface"
Q_DECLARE_INTERFACE(QPictureFormatInterface, QPictureFormatInterface_iid)


class Q_GUI_EXPORT QPictureFormatPlugin : public QObject, public QPictureFormatInterface
{
    Q_OBJECT
    Q_INTERFACES(QPictureFormatInterface:QFactoryInterface)
public:
    explicit QPictureFormatPlugin(QObject *parent = 0);
    ~QPictureFormatPlugin();

    virtual QStringList keys() const = 0;
    virtual bool loadPicture(const QString &format, const QString &filename, QPicture *pic);
    virtual bool savePicture(const QString &format, const QString &filename, const QPicture &pic);
    virtual bool installIOHandler(const QString &format) = 0;

};

#endif // QT_NO_LIBRARY || QT_NO_PICTURE
#endif // QPICTUREFORMATPLUGIN_H
