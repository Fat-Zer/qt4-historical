/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef SVGALIBSURFACE_H
#define SVGALIBSURFACE_H

#include "svgalibpaintengine.h"
#include "svgalibpaintdevice.h"
#include <private/qwindowsurface_qws_p.h>

class SvgalibPaintDevice;

class SvgalibSurface : public QWSWindowSurface
{
public:
    SvgalibSurface();
    SvgalibSurface(QWidget *w);
    ~SvgalibSurface();

    void setGeometry(const QRect &rect);
    bool isValid() const { return true; }
    bool scroll(const QRegion &region, int dx, int dy);
    QString key() const { return QLatin1String("svgalib"); }

    bool attach(const QByteArray &) { return true; }
    void detach() {}

    QImage image() const { return QImage(); }
    QPaintDevice *paintDevice() { return pdevice; }
    QPoint painterOffset() const;

private:
    SvgalibPaintDevice *pdevice;
};

#endif // SVGALIBSURFACE_H
