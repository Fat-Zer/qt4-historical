/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#ifndef Q3PAINTDEVICEMETRICS_H
#define Q3PAINTDEVICEMETRICS_H

#include "QtGui/qpaintdevice.h"


class Q_COMPAT_EXPORT Q3PaintDeviceMetrics                        // paint device metrics
{
public:
    Q3PaintDeviceMetrics(const QPaintDevice *device) : pdev(device) {}

    int width() const { return pdev->width(); }
    int height() const { return pdev->height(); }
    int widthMM() const { return pdev->widthMM(); }
    int heightMM() const { return pdev->heightMM(); }
    int logicalDpiX() const { return pdev->logicalDpiX(); }
    int logicalDpiY() const { return pdev->logicalDpiY(); }
    int physicalDpiX() const { return pdev->physicalDpiX(); }
    int physicalDpiY() const { return pdev->physicalDpiY(); }
    int numColors() const { return pdev->numColors(); }
    int depth() const { return pdev->depth(); }

private:
    const QPaintDevice *pdev;
};


#endif // QPAINTDEVICEMETRICS_H
