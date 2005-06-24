/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the opengl module of the Qt Toolkit.
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

#ifndef QGL_P_H
#define QGL_P_H

#include "private/qwidget_p.h"
#include "qglcolormap.h"
#include "qgl.h"
#include "qmap.h"

class QGLContext;
class QGLOverlayWidget;
class QPixmap;
#ifdef Q_WS_MAC
class QMacWindowChangeEvent;
#endif

class QGLFormatPrivate
{
public:
    QGLFormatPrivate() {
	opts = QGL::DoubleBuffer | QGL::DepthBuffer | QGL::Rgba | QGL::DirectRendering;
	pln = 0;
	depthSize = accumSize = stencilSize = alphaSize = -1;
	numSamples = -1;
    }
    QGL::FormatOptions opts;
    int pln;
    int depthSize;
    int accumSize;
    int stencilSize;
    int alphaSize;
    int numSamples;
};

class QGLWidgetPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QGLWidget)
public:
    QGLWidgetPrivate() : QWidgetPrivate() {}
    ~QGLWidgetPrivate() {}

    void init(QGLContext *context, const QGLWidget* shareWidget);
    bool renderCxPm(QPixmap *pixmap);
    void cleanupColormaps();

    QGLContext *glcx;
    bool autoSwap;

    QGLColormap cmap;
    QMap<QString, int> displayListCache;

#if defined(Q_WS_WIN)
    QGLContext *olcx;
#elif defined(Q_WS_X11)
    QGLOverlayWidget *olw;
#elif defined(Q_WS_MAC)
    QGLContext *olcx;
    void updatePaintDevice();
    QMacWindowChangeEvent *watcher;
#endif
};

class QGLContextPrivate
{
    Q_DECLARE_PUBLIC(QGLContext)
public:
    explicit QGLContextPrivate(QGLContext *context) : q_ptr(context) {}
    ~QGLContextPrivate() {}
    GLuint bindTexture(const QImage &image, GLenum target, GLint format, const QString &key);
    void init(QPaintDevice *dev, const QGLFormat &format);

#if defined(Q_WS_WIN)
    HGLRC rc;
    HDC dc;
    WId        win;
    int pixelFormatId;
    QGLCmap* cmap;
    HBITMAP hbitmap;
    HDC hbitmap_hdc;
#elif defined(Q_WS_X11) || defined(Q_WS_MAC)
    void* vi;
    void* cx;
#if defined(Q_WS_X11)
    quint32 gpm;
#endif
#endif
    QGLFormat glFormat;
    QGLFormat reqFormat;

    uint valid : 1;
    uint sharing : 1;
    uint initDone : 1;
    uint crWin : 1;
    QPaintDevice *paintDevice;
    QColor transpColor;
    QGLContext *q_ptr;
};

// GL extension definitions
class QGLExtensions {
public:
    enum Extension {
	TextureRectangle 	= 0x00000001,
	SampleBuffers 		= 0x00000002,
	GenerateMipmap 		= 0x00000004,
	TextureCompression 	= 0x00000008
    };
    Q_DECLARE_FLAGS(Extensions, Extension)

    static Extensions glExtensions;
    static void init(); // sys dependent
    static void init_extensions(); // general: called by init()
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QGLExtensions::Extensions)

/* NV_texture_rectangle */
#ifndef GL_NV_texture_rectangle
#define GL_TEXTURE_RECTANGLE_NV           0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_NV   0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_NV     0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_NV  0x84F8
#endif
#endif // QGL_P_H
