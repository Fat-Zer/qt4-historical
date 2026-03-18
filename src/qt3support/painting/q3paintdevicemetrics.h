/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt3Support module of the Qt Toolkit.
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

#ifndef Q3PAINTDEVICEMETRICS_H
#define Q3PAINTDEVICEMETRICS_H

#include "QtGui/qpaintdevice.h"

QT_MODULE(Qt3SupportLight)

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
