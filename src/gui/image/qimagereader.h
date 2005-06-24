/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the painting module of the Qt Toolkit.
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

#ifndef QIMAGEREADER_H
#define QIMAGEREADER_H

#include <QtCore/qbytearray.h>

class QIODevice;
class QImage;
class QRect;
class QSize;

class QImageReaderPrivate;
class Q_GUI_EXPORT QImageReader
{
public:
    enum ImageReaderError {
        UnknownError,
        FileNotFoundError,
        DeviceError,
        UnsupportedFormatError,
        InvalidDataError
    };

    QImageReader();
    explicit QImageReader(QIODevice *device, const QByteArray &format = QByteArray());
    explicit QImageReader(const QString &fileName, const QByteArray &format = QByteArray());
    ~QImageReader();

    void setFormat(const QByteArray &format);
    QByteArray format() const;

    void setDevice(QIODevice *device);
    QIODevice *device() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

    QSize size() const;

    void setClipRect(const QRect &rect);
    QRect clipRect() const;

    void setScaledSize(const QSize &size);
    QSize scaledSize() const;

    void setScaledClipRect(const QRect &rect);
    QRect scaledClipRect() const;

    bool canRead() const;
    QImage read();

    bool jumpToNextImage();
    bool jumpToImage(int imageNumber);
    int loopCount() const;
    int imageCount() const;
    int nextImageDelay() const;
    int currentImageNumber() const;
    QRect currentImageRect() const;

    ImageReaderError error() const;
    QString errorString() const;

    static QByteArray imageFormat(const QString &fileName);
    static QByteArray imageFormat(QIODevice *device);
    static QList<QByteArray> supportedImageFormats();

private:
    Q_DISABLE_COPY(QImageReader)
    QImageReaderPrivate *d;
};

#endif
