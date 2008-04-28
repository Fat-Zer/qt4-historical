/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#include <qscreenproxy_qws.h>

#ifndef QT_NO_QWS_PROXYSCREEN

#include <qregexp.h>

/*!
    \class QProxyScreen
    \ingroup qws
    \brief The QProxyScreen class provides a generic interface to QScreen implementations.
*/

/*!
    Constructs a proxy screen with the given \a displayId and \a classId.
*/
QProxyScreen::QProxyScreen(int displayId, QScreen::ClassId classId)
    : QScreen(displayId, classId), realScreen(0), d_ptr(0)
{
}

/*!
    Destroys the proxy screen.
*/
QProxyScreen::~QProxyScreen()
{
}

/*!
    Sets the real \a screen to be used by the proxy screen.

    \sa screen()
*/
void QProxyScreen::setScreen(QScreen *screen)
{
    realScreen = screen;
    configure();
}

/*!
    Returns the real screen used by the proxy screen.

    \sa setScreen()
*/
QScreen* QProxyScreen::screen() const
{
    return realScreen;
}


/*!
    \internal
*/
void QProxyScreen::configure()
{
    if (!realScreen)
        return;

    d = realScreen->depth();
    w = realScreen->width();
    h = realScreen->height();
    dw = realScreen->deviceWidth();
    dh = realScreen->deviceHeight();
    lstep = realScreen->linestep();
    data = realScreen->base();
    lstep = realScreen->linestep();
    size = realScreen->screenSize();
    physWidth = realScreen->physicalWidth();
    physHeight = realScreen->physicalHeight();
    pixeltype = realScreen->pixelType();
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
    setFrameBufferLittleEndian(realScreen->frameBufferLittleEndian());
#endif

    setOffset(realScreen->offset());
    setPixelFormat(realScreen->pixelFormat());
}

/*!
    \internal
    Returns the display ID that corresponds to the given \a spec.
*/
static int getDisplayId(const QString &spec)
{
    QRegExp regexp(QLatin1String(":(\\d+)\\b"));
    if (regexp.lastIndexIn(spec) != -1) {
        const QString capture = regexp.cap(1);
        return capture.toInt();
    }
    return 0;
}

/*!
    \reimp
*/
bool QProxyScreen::connect(const QString &displaySpec)
{
    const int id = getDisplayId(displaySpec);
    realScreen = qt_get_screen(id, displaySpec.toLatin1().constData());
    configure();

    return true;
}

/*!
    \reimp
*/
void QProxyScreen::exposeRegion(QRegion r, int changing)
{
    if (!realScreen) {
        QScreen::exposeRegion(r, changing);
        return;
    }

    realScreen->exposeRegion(r, changing);

    const QVector<QRect> rects = r.rects();
    for (int i = 0; i < rects.size(); ++i)
        setDirty(rects.at(i));
}

/*!
    \reimp
*/
void QProxyScreen::blit(const QImage &image, const QPoint &topLeft,
                        const QRegion &region)
{
    if (!realScreen) {
        QScreen::blit(image, topLeft, region);
        return;
    }

    realScreen->blit(image, topLeft, region);
}

/*!
    \reimp
*/
void QProxyScreen::solidFill(const QColor &color, const QRegion &region)
{
    if (!realScreen) {
        QScreen::solidFill(color, region);
        return;
    }
    realScreen->solidFill(color, region);
}

/*!
    \reimp
*/
QSize QProxyScreen::mapToDevice(const QSize &s) const
{
    if (!realScreen)
        return QScreen::mapToDevice(s);

    return realScreen->mapToDevice(s);
}

/*!
    \reimp
*/
QSize QProxyScreen::mapFromDevice(const QSize &s) const
{
    if (!realScreen)
        return QScreen::mapFromDevice(s);

    return realScreen->mapFromDevice(s);
}

/*!
    \reimp
*/
QPoint QProxyScreen::mapToDevice(const QPoint &p, const QSize &s) const
{
    if (!realScreen)
        return QScreen::mapToDevice(p, s);

    return realScreen->mapToDevice(p, s);
}

/*!
    \reimp
*/
QPoint QProxyScreen::mapFromDevice(const QPoint &p, const QSize &s) const
{
    if (!realScreen)
        return QScreen::mapFromDevice(p, s);

    return realScreen->mapFromDevice(p, s);
}

/*!
    \reimp
*/
QRect QProxyScreen::mapToDevice(const QRect &r, const QSize &s) const
{
    if (!realScreen)
        return QScreen::mapToDevice(r, s);

    return realScreen->mapToDevice(r, s);
}

/*!
    \reimp
*/
QRect QProxyScreen::mapFromDevice(const QRect &r, const QSize &s) const
{
    if (!realScreen)
        return QScreen::mapFromDevice(r, s);

    return realScreen->mapFromDevice(r, s);
}

/*!
    \reimp
*/
QRegion QProxyScreen::mapToDevice(const QRegion &r, const QSize &s) const
{
    if (!realScreen)
        return QScreen::mapToDevice(r, s);

    return realScreen->mapToDevice(r, s);
}

/*!
    \reimp
*/
QRegion QProxyScreen::mapFromDevice(const QRegion &r, const QSize &s) const
{
    if (!realScreen)
        return QScreen::mapFromDevice(r, s);

    return realScreen->mapFromDevice(r, s);
}

/*!
    \reimp
*/
void QProxyScreen::disconnect()
{
    if (realScreen) {
        realScreen->disconnect();
        delete realScreen;
        realScreen = 0;
    }
}

/*!
*/
bool QProxyScreen::initDevice()
{
    if (realScreen)
        return realScreen->initDevice();

    return false;
}

/*!
    \reimp
*/
void QProxyScreen::shutdownDevice()
{
    if (realScreen)
        realScreen->shutdownDevice();
}

/*!
    \reimp
*/
void QProxyScreen::setMode(int w,int h, int d)
{
    if (realScreen) {
        realScreen->setMode(w, h, d);
    } else {
        QScreen::dw = QScreen::w = w;
        QScreen::dh = QScreen::h = h;
        QScreen::d = d;
    }
    configure();
    exposeRegion(region(), 0);
}

/*!
    \reimp
*/
bool QProxyScreen::supportsDepth(int depth) const
{
    if (realScreen)
        return realScreen->supportsDepth(depth);
    return false;
}

/*!
    \reimp
*/
void QProxyScreen::save()
{
    if (realScreen)
        realScreen->save();
    QScreen::save();
}

/*!
    \reimp
*/
void QProxyScreen::restore()
{
    if (realScreen)
        realScreen->restore();
    QScreen::restore();
}

/*!
    \reimp
*/
void QProxyScreen::blank(bool on)
{
    if (realScreen)
        realScreen->blank(on);
}

/*!
    \reimp
*/
bool QProxyScreen::onCard(const unsigned char *ptr) const
{
    if (realScreen)
        return realScreen->onCard(ptr);
    return false;
}

/*!
    \reimp
*/
bool QProxyScreen::onCard(const unsigned char *ptr, ulong &offset) const
{
    if (realScreen)
        return realScreen->onCard(ptr, offset);
    return false;
}

/*!
    \reimp
*/
bool QProxyScreen::isInterlaced() const
{
    if (realScreen)
        return realScreen->isInterlaced();
    return false;
}

/*!
    \reimp
*/
bool QProxyScreen::isTransformed() const
{
    if (realScreen)
        return realScreen->isTransformed();
    return QScreen::isTransformed();
}

/*!
\reimp
*/
int QProxyScreen::memoryNeeded(const QString &str)
{
    if (realScreen)
        return realScreen->memoryNeeded(str);
    else
        return QScreen::memoryNeeded(str);
}

/*!
\reimp
*/
int QProxyScreen::sharedRamSize(void *ptr)
{
    if (realScreen)
        return realScreen->sharedRamSize(ptr);
    else
        return QScreen::sharedRamSize(ptr);
}

/*!
\reimp
*/
void QProxyScreen::haltUpdates()
{
    if (realScreen)
        realScreen->haltUpdates();
}

/*!
\reimp
*/
void QProxyScreen::resumeUpdates()
{
    if (realScreen)
        realScreen->resumeUpdates();
}

/*!
    \reimp
*/
void QProxyScreen::setDirty(const QRect &rect)
{
    if (realScreen)
        realScreen->setDirty(rect);
}

/*!
    \reimp
*/
QWSWindowSurface* QProxyScreen::createSurface(QWidget *widget) const
{
    if (realScreen)
        return realScreen->createSurface(widget);

    return QScreen::createSurface(widget);
}

/*!
    \reimp
*/
QWSWindowSurface* QProxyScreen::createSurface(const QString &key) const
{
    if (realScreen)
        return realScreen->createSurface(key);

    return QScreen::createSurface(key);
}

/*!
    \reimp
*/
QList<QScreen*> QProxyScreen::subScreens() const
{
    if (realScreen)
        return realScreen->subScreens();

    return QScreen::subScreens();
}

/*!
    \reimp
*/
QRegion QProxyScreen::region() const
{
    if (realScreen)
        return realScreen->region();
    else
        return QScreen::region();
}

#endif // QT_NO_QWS_PROXYSCREEN
