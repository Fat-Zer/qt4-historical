/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the plugins of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QDIRECTFBSCREEN_H
#define QDIRECTFBSCREEN_H

#include <QtGui/qscreen_qws.h>

QT_BEGIN_HEADER

QT_MODULE(Gui)

#include <directfb.h>

#define Q_DIRECTFB_VERSION ((DIRECTFB_MAJOR_VERSION << 16) | (DIRECTFB_MINOR_VERION << 8) | DIRECTFB_MICRO_VERSION)

class QDirectFBScreenPrivate;

class Q_GUI_EXPORT QDirectFBScreen : public QScreen
{
public:
    QDirectFBScreen(int display_id);
    ~QDirectFBScreen();

    bool connect(const QString &displaySpec);
    void disconnect();
    bool initDevice();
    void shutdownDevice();

    void exposeRegion(QRegion r, int changing);
    void blit(const QImage &img, const QPoint &topLeft, const QRegion &region);
    void scroll(const QRegion &region, const QPoint &offset);
    void solidFill(const QColor &color, const QRegion &region);

    void setMode(int width, int height, int depth);
    void blank(bool on);

    QWSWindowSurface* createSurface(QWidget *widget) const;
    QWSWindowSurface* createSurface(const QString &key) const;

    static inline QDirectFBScreen* instance() {
        Q_ASSERT(QScreen::instance()->classId() == QScreen::DirectFBClass);
        return static_cast<QDirectFBScreen*>(QScreen::instance());
    }

    IDirectFB* dfb();
    IDirectFBSurface* dfbSurface();
#ifndef QT_NO_DIRECTFB_LAYER
    IDirectFBDisplayLayer* dfbDisplayLayer();
#endif

    static int depth(DFBSurfacePixelFormat format);

    static DFBSurfacePixelFormat getSurfacePixelFormat(const QImage &image);
    static DFBSurfaceDescription getSurfaceDescription(const QImage &image);
    static DFBSurfaceDescription getSurfaceDescription(const uint *buffer,
                                                       int length);
    static QImage::Format getImageFormat(DFBSurfacePixelFormat  format);

#ifndef QT_NO_DIRECTFB_PALETTE
    static void setSurfaceColorTable(IDirectFBSurface *surface,
                                     const QImage &image);
#endif

private:
    void compose(const QRegion &r);
    void blit(IDirectFBSurface *src, const QPoint &topLeft,
              const QRegion &region);

    QDirectFBScreenPrivate *d_ptr;
};

QT_END_HEADER

#endif // QDIRECTFBSCREEN_H
