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

#ifndef QBITMAP_H
#define QBITMAP_H

#include "QtGui/qpixmap.h"

QT_MODULE(Gui)

class QVariant;

class Q_GUI_EXPORT QBitmap : public QPixmap
{
public:
    QBitmap();
    QBitmap(const QPixmap &);
    QBitmap(int w, int h);
    explicit QBitmap(const QSize &);
    explicit QBitmap(const QString &fileName, const char *format=0);
    ~QBitmap();

    QBitmap &operator=(const QPixmap &);
    operator QVariant() const;

    inline void clear() { fill(Qt::color0); }

    static QBitmap fromImage(const QImage &image, Qt::ImageConversionFlags flags = Qt::AutoColor);
    static QBitmap fromData(const QSize &size, const uchar *bits,
                            QImage::Format monoFormat = QImage::Format_MonoLSB);

    QBitmap transformed(const QMatrix &) const;
#ifdef QT3_SUPPORT
    inline QT3_SUPPORT_CONSTRUCTOR QBitmap(int w, int h, bool clear);
    inline QT3_SUPPORT_CONSTRUCTOR QBitmap(const QSize &, bool clear);
    QT3_SUPPORT_CONSTRUCTOR QBitmap(int w, int h, const uchar *bits, bool isXbitmap=false);
    QT3_SUPPORT_CONSTRUCTOR QBitmap(const QSize &, const uchar *bits, bool isXbitmap=false);
    inline QT3_SUPPORT QBitmap xForm(const QMatrix &matrix) const { return transformed(matrix); }
    QT3_SUPPORT_CONSTRUCTOR QBitmap(const QImage &image) { *this = fromImage(image); }
    QT3_SUPPORT QBitmap &operator=(const QImage &image) { *this = fromImage(image); return *this; }
#endif
};
Q_DECLARE_SHARED(QBitmap)

#ifdef QT3_SUPPORT
inline QBitmap::QBitmap(int w, int h, bool clear)
    : QPixmap(QSize(w, h), BitmapType)
{
    if (clear) this->clear();
}

inline QBitmap::QBitmap(const QSize &size, bool clear)
    : QPixmap(size, BitmapType)
{
    if (clear) this->clear();
}
#endif

#endif // QBITMAP_H
