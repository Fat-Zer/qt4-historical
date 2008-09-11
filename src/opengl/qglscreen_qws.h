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

#ifndef QSCREENEGL_P_H
#define QSCREENEGL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QScreenEGL class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/QScreen>
#include <QtOpenGL/qgl.h>
#include <GLES/egl.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(OpenGL)

class QGLScreenPrivate;

class Q_OPENGL_EXPORT QGLScreenSurfaceFunctions
{
public:
    virtual bool createNativeWindow(QWidget *widget, NativeWindowType *native);
    virtual bool createNativePixmap(QPixmap *pixmap, NativePixmapType *native);
    virtual bool createNativeImage(QImage *image, NativePixmapType *native);
};

class Q_OPENGL_EXPORT QGLScreen : public QScreen
{
    Q_DECLARE_PRIVATE(QGLScreen)
public:
    QGLScreen(int displayId);
    virtual ~QGLScreen();

    enum Option
    {
        NoOptions       = 0,
        NativeWindows   = 1,
        NativePixmaps   = 2,
        NativeImages    = 4,
        Overlays        = 8
    };
    Q_DECLARE_FLAGS(Options, Option)

    QGLScreen::Options options() const;

    virtual bool chooseContext(QGLContext *context, const QGLContext *shareContext);
    virtual bool hasOpenGL() = 0;

    QGLScreenSurfaceFunctions *surfaceFunctions() const;

protected:
    void setOptions(QGLScreen::Options value);
    void setSurfaceFunctions(QGLScreenSurfaceFunctions *functions);

private:
    QGLScreenPrivate *d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QGLScreen::Options)

QT_END_NAMESPACE

QT_END_HEADER

#endif // QSCREENEGL_P_H
