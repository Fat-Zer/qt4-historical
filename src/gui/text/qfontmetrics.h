/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the text module of the Qt Toolkit.
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

#ifndef QFONTMETRICS_H
#define QFONTMETRICS_H

#include "QtGui/qfont.h"
#ifndef QT_INCLUDE_COMPAT
#include "QtCore/qrect.h"
#endif

#ifdef Q_WS_QWS
class QFontEngine;
#endif

class QTextCodec;
class QRect;


class Q_GUI_EXPORT QFontMetrics
{
public:
    QFontMetrics(const QFont &);
    QFontMetrics(const QFont &, QPaintDevice *pd);
    QFontMetrics(const QFontMetrics &);
    ~QFontMetrics();

    QFontMetrics &operator=(const QFontMetrics &);

    int ascent() const;
    int descent() const;
    int height() const;
    int leading() const;
    int lineSpacing() const;
    int minLeftBearing() const;
    int minRightBearing() const;
    int maxWidth() const;

    bool inFont(QChar) const;

    int leftBearing(QChar) const;
    int rightBearing(QChar) const;
    int width(const QString &, int len = -1) const;

    int width(QChar) const;
    int charWidth(const QString &str, int pos) const;

    QRect boundingRect(QChar) const;

    QRect boundingRect(const QString &text) const;
    QRect boundingRect(const QRect &r, int flags, const QString &text, int tabstops=0, int *tabarray=0) const;
    inline QRect boundingRect(int x, int y, int w, int h, int flags, const QString &text,
                              int tabstops=0, int *tabarray=0) const
        { return boundingRect(QRect(x, y, w, h), flags, text, tabstops, tabarray); }
    QSize size(int flags, const QString& str, int tabstops=0, int *tabarray=0) const;

    int underlinePos() const;
    int overlinePos() const;
    int strikeOutPos() const;
    int lineWidth() const;

    bool operator==(const QFontMetrics &other);
    inline bool operator !=(const QFontMetrics &other) { return !operator==(other); }

#ifdef QT3_SUPPORT
    inline QRect boundingRect(const QString &text, int len) const
        { return boundingRect(text.left(len)); }
    inline QRect boundingRect(int x, int y, int w, int h, int flags, const QString& str, int len,
                              int tabstops=0, int *tabarray=0) const
        { return boundingRect(QRect(x, y, w, h), flags, str.left(len), tabstops, tabarray); }
    inline QSize size(int flags, const QString& str, int len, int tabstops=0, int *tabarray=0) const
        { return size(flags, str.left(len), tabstops, tabarray); }
#endif
private:
#if defined(Q_WS_MAC)
    friend class QFontPrivate;
#endif

    QFontPrivate *d;
};


class Q_GUI_EXPORT QFontMetricsF
{
public:
    QFontMetricsF(const QFont &);
    QFontMetricsF(const QFont &, QPaintDevice *pd);
    QFontMetricsF(const QFontMetrics &);
    QFontMetricsF(const QFontMetricsF &);
    ~QFontMetricsF();

    QFontMetricsF &operator=(const QFontMetricsF &);
    QFontMetricsF &operator=(const QFontMetrics &);

    qreal ascent() const;
    qreal descent() const;
    qreal height() const;
    qreal leading() const;
    qreal lineSpacing() const;
    qreal minLeftBearing() const;
    qreal minRightBearing() const;
    qreal maxWidth() const;

    bool inFont(QChar) const;

    qreal leftBearing(QChar) const;
    qreal rightBearing(QChar) const;
    qreal width(const QString &string) const;

    qreal width(QChar) const;

    QRectF boundingRect(const QString &string) const;
    QRectF boundingRect(QChar) const;
    QRectF boundingRect(const QRectF &r, int flags, const QString& string, int tabstops=0, int *tabarray=0) const;
    QSizeF size(int flags, const QString& str, int tabstops=0, int *tabarray=0) const;

    qreal underlinePos() const;
    qreal overlinePos() const;
    qreal strikeOutPos() const;
    qreal lineWidth() const;

    bool operator==(const QFontMetricsF &other);
    inline bool operator !=(const QFontMetricsF &other) { return !operator==(other); }

private:
    QFontPrivate *d;
};

#endif // QFONTMETRICS_H
