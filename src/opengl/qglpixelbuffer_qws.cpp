/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
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

#include "qglpixelbuffer.h"
#include "qglpixelbuffer_p.h"
#include <GLES/egl.h>

#include <qimage.h>
#include <private/qgl_p.h>
#include <qdebug.h>

QT_BEGIN_NAMESPACE

#define QGL_PBUFFER_ATTRIBS_SIZE    32

static void qt_pbuffer_format_to_attribs(const QGLFormat& f, EGLint *configAttribs)
{
    int cfg = 0;
    configAttribs[cfg++] = EGL_RED_SIZE;
    configAttribs[cfg++] = f.redBufferSize() == -1 ? 1 : f.redBufferSize();
    configAttribs[cfg++] = EGL_GREEN_SIZE;
    configAttribs[cfg++] = f.greenBufferSize() == -1 ? 1 : f.greenBufferSize();
    configAttribs[cfg++] = EGL_BLUE_SIZE;
    configAttribs[cfg++] = f.blueBufferSize() == -1 ? 1 : f.blueBufferSize();
    if (f.alpha()) {
        configAttribs[cfg++] = EGL_ALPHA_SIZE;
        configAttribs[cfg++] = f.alphaBufferSize() == -1 ? 1 : f.alphaBufferSize();
    }
    if (f.depth()) {
        configAttribs[cfg++] = EGL_DEPTH_SIZE;
        configAttribs[cfg++] = f.depthBufferSize() == -1 ? 1 : f.depthBufferSize();
    }
    configAttribs[cfg++] = EGL_SURFACE_TYPE;
    configAttribs[cfg++] = EGL_PBUFFER_BIT;
    configAttribs[cfg++] = EGL_NONE;
}

bool QGLPixelBufferPrivate::init(const QSize &size, const QGLFormat &f, QGLWidget *shareWidget)
{
    // Choose an appropriate configuration on the display.
    dpy = qt_qgl_egl_display();
    if (dpy == EGL_NO_DISPLAY)
        return false;
    EGLint attribs[QGL_PBUFFER_ATTRIBS_SIZE];
    qt_pbuffer_format_to_attribs(f, attribs);
    EGLint matching = 0;
    if (!eglChooseConfig(dpy, attribs, &config, 1, &matching) || matching < 1) {
        qWarning("QGLPixelBufferPrivate::init(): Could not find a suitable EGL configuration");
        return false;
    }

    // Retrieve the actual format properties.
    EGLint value = 0;
    eglGetConfigAttrib(dpy, config, EGL_RED_SIZE, &value);
    format.setRedBufferSize(value);
    eglGetConfigAttrib(dpy, config, EGL_GREEN_SIZE, &value);
    format.setGreenBufferSize(value);
    eglGetConfigAttrib(dpy, config, EGL_BLUE_SIZE, &value);
    format.setBlueBufferSize(value);
    eglGetConfigAttrib(dpy, config, EGL_ALPHA_SIZE, &value);
    format.setAlpha(value != 0);
    if (format.alpha())
        format.setAlphaBufferSize(value);
    eglGetConfigAttrib(dpy, config, EGL_DEPTH_SIZE, &value);
    format.setDepth(value != 0);
    if (format.depth())
        format.setDepthBufferSize(value);
    if (eglGetConfigAttrib(dpy, config, EGL_LEVEL, &value))
        format.setPlane(value);
    eglGetConfigAttrib(dpy, config, EGL_SAMPLE_BUFFERS, &value);
    format.setSampleBuffers(value != 0);
    if (format.sampleBuffers()) {
        eglGetConfigAttrib(dpy, config, EGL_SAMPLES, &value);
        format.setSamples(value);
    }
    eglGetConfigAttrib(dpy, config, EGL_STENCIL_SIZE, &value);
    format.setStencil(value != 0);
    if (format.stencil())
        format.setStencilBufferSize(value);

    // Create the attributes needed for the pbuffer.
    int cfg = 0;
    attribs[cfg++] = EGL_WIDTH;
    attribs[cfg++] = size.width();
    attribs[cfg++] = EGL_HEIGHT;
    attribs[cfg++] = size.height();
    attribs[cfg++] = EGL_NONE;

    // Create the pbuffer surface.
    pbuf = eglCreatePbufferSurface(dpy, config, attribs);
    if (pbuf == EGL_NO_SURFACE) {
        qWarning("QGLPixelBufferPrivate::init(): Unable to create EGL pbuffer surface");
        return false;
    }

    // Create a new context for the configuration.
    EGLContext shareContext = 0;
    if (shareWidget && shareWidget->d_func()->glcx)
        shareContext = shareWidget->d_func()->glcx->d_func()->cx;
    ctx = 0;
    if (shareContext) {
        ctx = eglCreateContext(dpy, config, shareContext, 0);
        if (!ctx)
            qWarning("QGLPixelBufferPrivate::init(): Could not share context");
    }
    if (!ctx) {
        ctx = eglCreateContext(dpy, config, 0, 0);
        if (!ctx) {
            qWarning("QGLPixelBufferPrivate::init(): Unable to create EGL context");
            eglDestroySurface(dpy, pbuf);
            pbuf = 0;
            return false;
        }
    }

    return true;
}

bool QGLPixelBufferPrivate::cleanup()
{
    eglDestroySurface(dpy, pbuf);
    return true;
}

bool QGLPixelBuffer::bindToDynamicTexture(GLuint texture_id)
{
    Q_UNUSED(texture_id);
    return false;
}

void QGLPixelBuffer::releaseFromDynamicTexture()
{
}


GLuint QGLPixelBuffer::generateDynamicTexture() const
{
    return 0;
}

bool QGLPixelBuffer::hasOpenGLPbuffers()
{
    EGLDisplay dpy = qt_qgl_egl_display();
    if (dpy == EGL_NO_DISPLAY)
        return false;

    // See if we have at least 1 configuration that matches the default format.
    EGLint attribs[QGL_PBUFFER_ATTRIBS_SIZE];
    qt_pbuffer_format_to_attribs(QGLFormat::defaultFormat(), attribs);
    EGLConfig config = 0;
    EGLint matching = 0;
    if (!eglChooseConfig(dpy, attribs, &config, 1, &matching) || matching < 1)
        return false;

    return true;
}

QT_END_NAMESPACE
