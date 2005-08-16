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

#include "qpaintdevice.h"
#include "qpainter.h"
#include "qwidget.h"
#include "qbitmap.h"
#include "qapplication.h"
#include <private/qapplication_p.h>
#include "qt_windows.h"
#include "qprinter.h"

QPaintDevice::QPaintDevice()
{
    if (!qApp) {                                // global constructor
        qFatal("QPaintDevice: Must construct a QApplication before a "
                "QPaintDevice");
        return;
    }
    painters = 0;
}

QPaintDevice::~QPaintDevice()
{
    if (paintingActive())
        qWarning("QPaintDevice: Cannot destroy paint device that is being "
                  "painted.  Be sure to QPainter::end() painters!");
}

int QPaintDevice::metric(PaintDeviceMetric) const
{
    qWarning("QPaintDevice::metrics: Device has no metric information");
    return 0;
}


/*! \internal
*/
HDC QPaintDevice::getDC() const
{
    return 0;
}

/*! \internal
*/
void QPaintDevice::releaseDC(HDC) const
{
}
