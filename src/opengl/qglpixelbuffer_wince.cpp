/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include "qglpixelbuffer.h"
#include "qglpixelbuffer_p.h"
#include <GLES/egl.h>

#include <qimage.h>
#include <private/qgl_p.h>
#include <qdebug.h>

QT_BEGIN_NAMESPACE

#ifndef GL_TEXTURE_RECTANGLE_EXT
#define GL_TEXTURE_RECTANGLE_EXT 0x84F5
#endif

bool QGLPixelBufferPrivate::init(const QSize &size, const QGLFormat &f, QGLWidget *shareWidget)
{
    Q_UNUSED(size);
    Q_UNUSED(f);
    Q_UNUSED(shareWidget);
    return false;
}

bool QGLPixelBufferPrivate::cleanup()
{
    return false;
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
    return false;
}

QT_END_NAMESPACE
