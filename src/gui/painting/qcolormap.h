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

#ifndef QCOLORMAP_H
#define QCOLORMAP_H

#include <QtCore/qatomic.h>
#include <QtGui/qrgb.h>
#include <QtCore/qvector.h>
#include <QtGui/qwindowdefs.h>

class QColor;
class QColormapPrivate;

class Q_GUI_EXPORT QColormap
{
public:
    enum Mode { Direct, Indexed, Gray };

    static void initialize();
    static void cleanup();

    static QColormap instance(int screen = -1);

    QColormap(const QColormap &colormap);
    ~QColormap();

    QColormap &operator=(const QColormap &colormap);

    Mode mode() const;

    int depth() const;
    int size() const;

    uint pixel(const QColor &color) const;
    const QColor colorAt(uint pixel) const;

    const QVector<QColor> colormap() const;

#ifdef Q_WS_WIN
    static HPALETTE hPal();
#endif

private:
    QColormap();
    QColormapPrivate *d;
};

#endif // QCOLORMAP_H
