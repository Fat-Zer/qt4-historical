/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
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


#include <qgl.h>
#include <qlist.h>
#include <qmap.h>
#include <qpixmap.h>
#include <qevent.h>
#include <private/qgl_p.h>
#include <qcolormap.h>
#include <qvarlengtharray.h>
#include <qdebug.h>

#include <windows.h>

#include <GLES/egl.h>
#include <GLES/gl.h>

#include "qgl_cl_p.h"


QT_BEGIN_NAMESPACE


class QGLCmapPrivate
{
public:
    QGLCmapPrivate() : count(1) { }
    void ref()                { ++count; }
    bool deref()        { return !--count; }
    uint count;

    enum AllocState{ UnAllocated = 0, Allocated = 0x01, Reserved = 0x02 };

    int maxSize;
    QVector<uint> colorArray;
    QVector<quint8> allocArray;
    QVector<quint8> contextArray;
    QMap<uint,int> colorMap;
};

/*****************************************************************************
  QColorMap class - temporarily here, until it is ready for prime time
 *****************************************************************************/

/****************************************************************************
**
** Definition of QColorMap class
**
****************************************************************************/

#ifndef QGLCMAP_H
#define QGLCMAP_H

#include <qcolor.h>




/*****************************************************************************
  QGLFormat Win32/WGL-specific code
 *****************************************************************************/


void qwglError(const char* method, const char* func)
{
#ifndef QT_NO_DEBUG
    wchar_t *lpMsgBuf;
    FormatMessage(
                  FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                  0, GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPWSTR) &lpMsgBuf, 0, 0);
    qWarning("%s : %s failed: %s", method, func, QString::fromUtf16((ushort*)lpMsgBuf));
    LocalFree(lpMsgBuf);
#else
    Q_UNUSED(method);
    Q_UNUSED(func);
#endif
}


bool QGLFormat::hasOpenGL()
{
    return true;
}

static bool opengl32dll = false;

bool QGLFormat::hasOpenGLOverlays()
{
    return false; // ###
}


bool QGLContext::chooseContext(const QGLContext* shareContext)
{
    Q_D(QGLContext);

    d->cx = 0;

    EGLint matchingConfigs;
    EGLint configAttribs[] = {
        EGL_RED_SIZE,        5,
        EGL_GREEN_SIZE,      6,
        EGL_BLUE_SIZE,       5,
        EGL_ALPHA_SIZE,      0,
        EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,
        EGL_NONE
    };

    bool result = true;
    HDC myDc;

    // NB! the QGLTempContext object is needed for the
    // wglGetProcAddress() calls to succeed and are absolutely
    // necessary - don't remove!
    //QGLTempContext tmp_ctx;

    if (deviceIsPixmap()) {
        return false;
    } else {
        d->win = ((QWidget*)d->paintDevice)->winId();
        myDc = GetDC(d->win);
    }
    d->dpy = eglGetDisplay(myDc);


    if (!eglInitialize(d->dpy, NULL, NULL))
        return false;

        if (!eglChooseConfig(d->dpy, configAttribs, &d->config, 1,&matchingConfigs))
        return false;

    if (matchingConfigs < 1)
        return false;

    EGLContext ctx = eglCreateContext(d->dpy, d->config, 0, 0);
    //(shareContext ? shareContext->d_func()->cx : 0),
    //configAttribs);
    if(!ctx) {
        GLenum err = eglGetError();
        qDebug("eglCreateContext err %x", err);
        if(err == EGL_BAD_MATCH || err == EGL_BAD_CONTEXT) {
            if(shareContext && shareContext->d_func()->cx) {
                qWarning("QGLContext::chooseContext(): Context sharing mismatch!");
                if(!(ctx = eglCreateContext(d->dpy, d->config, 0, configAttribs)))
                    return false;
                shareContext = 0;
            }
        }
        if(!ctx) {
            qWarning("QGLContext::chooseContext(): Unable to create QGLContext");
            return false;
        }
    }

    d->cx = ctx;
    if (shareContext && shareContext->d_func()->cx) {
        QGLContext *share = const_cast<QGLContext *>(shareContext);
        d->sharing = true;
        share->d_func()->sharing = true;
    }

    d->surface = eglCreateWindowSurface(d->dpy, d->config, d->win, 0);


    if (!d->surface)
        return false;


    if (!myDc) {
        qWarning("QGLContext::chooseContext(): Paint device cannot be null");
        result = false;
    }

    if (!eglMakeCurrent(d->dpy, d->surface, d->surface, d->cx)) {
        GLenum err = eglGetError();
        qDebug("eglMakeCurrent err %x", err);
    }
    glClearColor(0.0,0.0,0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(d->dpy, d->surface);

    if (d->win)
        ReleaseDC(d->win, myDc);

    return result;
}



static bool qLogEq(bool a, bool b)
{
    return (((!a) && (!b)) || (a && b));
}

int QGLContext::choosePixelFormat(void* , HDC )
{

    return 0;
}

class QGLCmapPrivate;

class /*Q_EXPORT*/ QGLCmap
{
public:
    enum Flags { Reserved = 0x01 };

    QGLCmap(int maxSize = 256);
    QGLCmap(const QGLCmap& map);
    ~QGLCmap();

    QGLCmap& operator=(const QGLCmap& map);

    // isEmpty and/or isNull ?
    int size() const;
    int maxSize() const;

    void resize(int newSize);

    int find(QRgb color) const;
    int findNearest(QRgb color) const;
    int allocate(QRgb color, uint flags = 0, quint8 context = 0);

    void setEntry(int idx, QRgb color, uint flags = 0, quint8 context = 0);

    const QRgb* colors() const;

private:
    void detach();
    QGLCmapPrivate* d;
};

#endif


QGLCmap::QGLCmap(int maxSize) // add a bool prealloc?
{
    d = new QGLCmapPrivate;
    d->maxSize = maxSize;
}

QGLCmap::QGLCmap(const QGLCmap& map)
{
    d = map.d;
    d->ref();
}

QGLCmap::~QGLCmap()
{
    if (d && d->deref())
        delete d;
    d = 0;
}

QGLCmap& QGLCmap::operator=(const QGLCmap& map)
{
    map.d->ref();
    if (d->deref())
        delete d;
    d = map.d;
    return *this;
}

int QGLCmap::size() const
{
    return d->colorArray.size();
}

int QGLCmap::maxSize() const
{
    return d->maxSize;
}

void QGLCmap::detach()
{
    if (d->count != 1) {
        d->deref();
        QGLCmapPrivate* newd = new QGLCmapPrivate;
        newd->maxSize = d->maxSize;
        newd->colorArray = d->colorArray;
        newd->allocArray = d->allocArray;
        newd->contextArray = d->contextArray;
        newd->colorArray.detach();
        newd->allocArray.detach();
        newd->contextArray.detach();
        newd->colorMap = d->colorMap;
        d = newd;
    }
}


void QGLCmap::resize(int newSize)
{
    if (newSize < 0 || newSize > d->maxSize) {
        qWarning("QGLCmap::resize(): size out of range");
        return;
    }
    int oldSize = size();
    detach();
    //if shrinking; remove the lost elems from colorMap
    d->colorArray.resize(newSize);
    d->allocArray.resize(newSize);
    d->contextArray.resize(newSize);
    if (newSize > oldSize) {
        memset(d->allocArray.data() + oldSize, 0, newSize - oldSize);
        memset(d->contextArray.data() + oldSize, 0, newSize - oldSize);
    }
}


int QGLCmap::find(QRgb color) const
{
    QMap<uint,int>::ConstIterator it = d->colorMap.find(color);
    if (it != d->colorMap.end())
        return *it;
    return -1;
}


int QGLCmap::findNearest(QRgb color) const
{
    int idx = find(color);
    if (idx >= 0)
        return idx;
    int mapSize = size();
    int mindist = 200000;
    int r = qRed(color);
    int g = qGreen(color);
    int b = qBlue(color);
    int rx, gx, bx, dist;
    for (int i=0; i < mapSize; i++) {
        if (!(d->allocArray[i] & QGLCmapPrivate::Allocated))
            continue;
        QRgb ci = d->colorArray[i];
        rx = r - qRed(ci);
        gx = g - qGreen(ci);
        bx = b - qBlue(ci);
        dist = rx*rx + gx*gx + bx*bx;                // calculate distance
        if (dist < mindist) {                        // minimal?
            mindist = dist;
            idx = i;
        }
    }
    return idx;
}


// Does not always allocate; returns existing c idx if found

int QGLCmap::allocate(QRgb color, uint flags, quint8 context)
{
    int idx = find(color);
    if (idx >= 0)
        return idx;

    int mapSize = d->colorArray.size();
    int newIdx = d->allocArray.indexOf(QGLCmapPrivate::UnAllocated);

    if (newIdx < 0) {                        // Must allocate more room
        if (mapSize < d->maxSize) {
            newIdx = mapSize;
            mapSize++;
            resize(mapSize);
        }
        else {
            //# add a bool param that says what to do in case no more room -
            // fail (-1) or return nearest?
            return -1;
        }
    }

    d->colorArray[newIdx] = color;
    if (flags & QGLCmap::Reserved) {
        d->allocArray[newIdx] = QGLCmapPrivate::Reserved;
    }
    else {
        d->allocArray[newIdx] = QGLCmapPrivate::Allocated;
        d->colorMap.insert(color, newIdx);
    }
    d->contextArray[newIdx] = context;
    return newIdx;
}


void QGLCmap::setEntry(int idx, QRgb color, uint flags, quint8 context)
{
    if (idx < 0 || idx >= d->maxSize) {
        qWarning("QGLCmap::set(): Index out of range");
        return;
    }
    detach();
    int mapSize = size();
    if (idx >= mapSize) {
        mapSize = idx + 1;
        resize(mapSize);
    }
    d->colorArray[idx] = color;
    if (flags & QGLCmap::Reserved) {
        d->allocArray[idx] = QGLCmapPrivate::Reserved;
    }
    else {
        d->allocArray[idx] = QGLCmapPrivate::Allocated;
        d->colorMap.insert(color, idx);
    }
    d->contextArray[idx] = context;
}


const QRgb* QGLCmap::colors() const
{
    return d->colorArray.data();
}


void QGLContext::reset()
{
    Q_D(QGLContext);
    // workaround for matrox driver:
    // make a cheap call to opengl to force loading of DLL

    if (!d->valid)
        return;
    doneCurrent();

    if (d->cx)
        eglDestroyContext(d->dpy, d->cx);


    d->cx = 0;
    d->rc  = 0;
    if (d->win && d->dc)
        ReleaseDC(d->win, d->dc);

    d->dc  = 0;
    d->win = 0;
    d->pixelFormatId = 0;
    d->sharing = false;
    d->valid = false;
    d->transpColor = QColor();
    delete d->cmap;
    d->cmap = 0;
    d->initDone = false;
    qgl_share_reg()->removeShare(this);
}


//
// NOTE: In a multi-threaded environment, each thread has a current
// context. If we want to make this code thread-safe, we probably
// have to use TLS (thread local storage) for keeping current contexts.
//

void QGLContext::makeCurrent()
{
    Q_D(QGLContext);
    if(!d->valid) {
        qWarning("QGLContext::makeCurrent(): Cannot make invalid context current");
        return;
    }


    bool ok = eglMakeCurrent(d->dpy, d->surface, d->surface, d->cx);
    if (!ok) {
        EGLint err = eglGetError();
        qWarning("QGLContext::makeCurrent(): Failed %x.", err);
    }
    if (ok) {

        if (!qgl_context_storage.hasLocalData() && QThread::currentThread())
            qgl_context_storage.setLocalData(new QGLThreadContext);
        if (qgl_context_storage.hasLocalData())
            qgl_context_storage.localData()->context = this;
        currentCtx = this;

    }

}


void QGLContext::doneCurrent()
{
    Q_D(QGLContext);
    currentCtx = 0;
    eglMakeCurrent(d->dpy, d->surface, d->surface, 0);
    if (qgl_context_storage.hasLocalData())
        qgl_context_storage.localData()->context = 0;
    if (deviceIsPixmap() && d->hbitmap) {
        QPixmap *pm = static_cast<QPixmap *>(d->paintDevice);
        *pm = QPixmap::fromWinHBITMAP(d->hbitmap);
    }
    if (d->win && d->dc)
        ReleaseDC(d->win, d->dc);
    d->dc = 0;
}

void QGLContext::swapBuffers() const
{
    Q_D(const QGLContext);
    eglSwapBuffers(d->dpy, d->surface);
}


QColor QGLContext::overlayTransparentColor() const
{
    return d_func()->transpColor;
}


void QGLContext::generateFontDisplayLists(const QFont & fnt, int listBase)
{
    Q_UNUSED(fnt);
    Q_UNUSED(listBase);
}

void *QGLContext::getProcAddress(const QString &proc) const
{
    return (void*)eglGetProcAddress(reinterpret_cast<const char *>(proc.toLatin1().data()));
}

/*****************************************************************************
  QGLWidget Win32/WGL-specific code
 *****************************************************************************/

void QGLWidgetPrivate::init(QGLContext *ctx, const QGLWidget* shareWidget)
{
    Q_Q(QGLWidget);
    olcx = 0;
    initContext(ctx, shareWidget);

    if (q->isValid() && q->context()->format().hasOverlay()) {
        olcx = new QGLContext(QGLFormat::defaultOverlayFormat(), q);
        if (!olcx->create(shareWidget ? shareWidget->overlayContext() : 0)) {
            delete olcx;
            olcx = 0;
            glcx->d_func()->glFormat.setOverlay(false);
        }
    } else {
        olcx = 0;
    }
}

/*\internal
  Store color values in the given colormap.
*/
static void qStoreColors(HPALETTE cmap, const QGLColormap & cols)
{
    QRgb color;
    PALETTEENTRY pe;

    for (int i = 0; i < cols.size(); i++) {
        color = cols.entryRgb(i);
        pe.peRed   = qRed(color);
        pe.peGreen = qGreen(color);
        pe.peBlue  = qBlue(color);
        pe.peFlags = 0;

        SetPaletteEntries(cmap, i, 1, &pe);
    }
}

void QGLWidgetPrivate::updateColormap()
{
    Q_Q(QGLWidget);
    if (!cmap.handle())
        return;
    HDC hdc = GetDC(q->winId());
    SelectPalette(hdc, (HPALETTE) cmap.handle(), TRUE);
    qStoreColors((HPALETTE) cmap.handle(), cmap);
    RealizePalette(hdc);
    ReleaseDC(q->winId(), hdc);
}

bool QGLWidget::event(QEvent *e)
{
    Q_D(QGLWidget);
    if (e->type() == QEvent::ParentChange) {
        setContext(new QGLContext(d->glcx->requestedFormat(), this));
        // the overlay needs to be recreated as well
        delete d->olcx;
        if (isValid() && context()->format().hasOverlay()) {
            d->olcx = new QGLContext(QGLFormat::defaultOverlayFormat(), this);
            if (!d->olcx->create(isSharing() ? d->glcx : 0)) {
                delete d->olcx;
                d->olcx = 0;
                d->glcx->d_func()->glFormat.setOverlay(false);
            }
        } else {
            d->olcx = 0;
        }
    } else if (e->type() == QEvent::Show && !format().rgba()) {
        d->updateColormap();
    }

    return QWidget::event(e);
}


void QGLWidget::setMouseTracking(bool enable)
{
    QWidget::setMouseTracking(enable);
}


void QGLWidget::resizeEvent(QResizeEvent *)
{
    Q_D(QGLWidget);
    if (!isValid())
        return;
    makeCurrent();
    if (!d->glcx->initialized())
        glInit();
    resizeGL(width(), height());
    if (d->olcx) {
        makeOverlayCurrent();
        resizeOverlayGL(width(), height());
    }
}


const QGLContext* QGLWidget::overlayContext() const
{
    return d_func()->olcx;
}


void QGLWidget::makeOverlayCurrent()
{
    Q_D(QGLWidget);
    if (d->olcx) {
        d->olcx->makeCurrent();
        if (!d->olcx->initialized()) {
            initializeOverlayGL();
            d->olcx->setInitialized(true);
        }
    }
}


void QGLWidget::updateOverlayGL()
{
    Q_D(QGLWidget);
    if (d->olcx) {
        makeOverlayCurrent();
        paintOverlayGL();
        if (d->olcx->format().doubleBuffer()) {
            if (d->autoSwap)
                d->olcx->swapBuffers();
        }
        else {
            glFlush();
        }
    }
}

void QGLWidget::setContext(QGLContext *context,
                            const QGLContext* shareContext,
                            bool deleteOldContext)
{
    Q_D(QGLWidget);
    if (context == 0) {
        qWarning("QGLWidget::setContext: Cannot set null context");
        return;
    }
    if (!context->deviceIsPixmap() && context->device() != this) {
        qWarning("QGLWidget::setContext: Context must refer to this widget");
        return;
    }

    if (d->glcx)
        d->glcx->doneCurrent();
    QGLContext* oldcx = d->glcx;
    d->glcx = context;

    bool doShow = false;
    if (oldcx && oldcx->d_func()->win == winId() && !d->glcx->deviceIsPixmap()) {
        // We already have a context and must therefore create a new
        // window since Windows does not permit setting a new OpenGL
        // context for a window that already has one set.
        doShow = isVisible();
        QWidget *pW = static_cast<QWidget *>(parent());
        QPoint pos = geometry().topLeft();
        setParent(pW, windowFlags());
        move(pos);
    }

    if (!d->glcx->isValid()) {
        d->glcx->create(shareContext ? shareContext : oldcx);
        // the above is a trick to keep disp lists etc when a
        // QGLWidget has been reparented, so remove the sharing
        // flag if we don't actually have a sharing context.
        if (!shareContext)
            d->glcx->d_ptr->sharing = false;
    }

    if (deleteOldContext)
        delete oldcx;

    if (doShow)
        show();
}


bool QGLWidgetPrivate::renderCxPm(QPixmap*)
{
    return false;
}

void QGLWidgetPrivate::cleanupColormaps()
{
    Q_Q(QGLWidget);
    if (cmap.handle()) {
        HDC hdc = GetDC(q->winId());
        SelectPalette(hdc, (HPALETTE) GetStockObject(DEFAULT_PALETTE), FALSE);
        DeleteObject((HPALETTE) cmap.handle());
        ReleaseDC(q->winId(), hdc);
        cmap.setHandle(0);
    }
    return;
}

const QGLColormap & QGLWidget::colormap() const
{
    return d_func()->cmap;
}

void QGLWidget::setColormap(const QGLColormap & c)
{
    Q_D(QGLWidget);
    d->cmap = c;

    if (d->cmap.handle()) { // already have an allocated cmap
        d->updateColormap();
    } else {
        LOGPALETTE *lpal = (LOGPALETTE *) malloc(sizeof(LOGPALETTE)
                                                 +c.size()*sizeof(PALETTEENTRY));
        lpal->palVersion    = 0x300;
        lpal->palNumEntries = c.size();
        d->cmap.setHandle(CreatePalette(lpal));
        free(lpal);
        d->updateColormap();
    }
}

void QGLExtensions::init()
{
    static bool init_done = false;

    if (init_done)
        return;
    init_done = true;
    init_extensions();
}

QT_END_NAMESPACE
