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

#include <QGLScreen>
#include <QGLContext>
#include <QGLWidget>
#include "private/qglwindowsurface_qws_p.h"

QT_BEGIN_NAMESPACE

class QGLScreenPrivate
{
public:
    QGLScreen::Options options;
    QGLScreenSurfaceFunctions *functions;
};

/*!
  \internal
  \preliminary
  \class QGLScreen

  \brief This class encapsulates an OpenGL screen driver.
*/

QGLScreen::QGLScreen(int displayId)
    : QScreen(displayId, GLClass), d_ptr(new QGLScreenPrivate)
{
    d_ptr->options = NoOptions;
    d_ptr->functions = new QGLScreenSurfaceFunctions();
}

QGLScreen::~QGLScreen()
{
    delete d_ptr->functions;
    delete d_ptr;
}

/*!
    \since 4.3

    Initializes the \a context and sets up the QGLWindowSurface of the
    QWidget of \a context based on the parameters of \a context and
    based on its own requirements.  The format() of \a context needs
    to be updated with the actual parameters of the OpenGLES drawable
    that was set up.

    \a shareContext is used in the same way as for QGLContext. It is
    the context with which \a context shares display lists and texture
    ids etc. The window surface must be set up so that this sharing
    works.

    Returns true in case of success and false if it is not possible to
    create the necessary OpenGLES drawable/context.

    Since 4.4.2, this function will be not be called if options()
    indicates that a native window or pixmap drawable can be created
    via the functions in the surfaceFunctions() object.

    \sa options()
*/
bool
QGLScreen::chooseContext(QGLContext *context, const QGLContext *shareContext)
{
    Q_UNUSED(shareContext);

    if (context->device()->devType() == QInternal::Widget) {
        QGLWidget *widget = static_cast<QGLWidget*>(context->device());
        QWSGLWindowSurface *surface =
	    static_cast<QWSGLWindowSurface*>(widget->windowSurface());
        surface->setContext(context);
        return true;
    }
    return false;
}

/*!
    \enum QGLScreen::Option
    This enum defines options that can be set on QGLScreen instances.

    \value NoOptions There are no special options on the screen.  This is the default.
    \value NativeWindows Native windows can be created with QGLScreenSurfaceFunctions::createNativeWindow().
    \value NativePixmaps Native pixmaps can be created with QGLScreenSurfaceFunctions::createNativePixmap().
    \value NativeImages Native images can be created with QGLScreenSurfaceFunctions::createNativeImage().
    \value Overlays The screen supports GL overlays.
*/

/*!
    \since 4.4.2

    Returns the options associated with this QGLScreen.

    \sa setOptions()
*/
QGLScreen::Options QGLScreen::options() const
{
    return d_ptr->options;
}

/*!
    \since 4.4.2

    Sets the options associated with this QGLScreen to \a value.

    \sa options()
*/
void QGLScreen::setOptions(QGLScreen::Options value)
{
    d_ptr->options = value;
}

/*!
    \since 4.4.2

    Returns the surface functions object for this QGLScreen.

    \sa setSurfaceFunctions()
*/
QGLScreenSurfaceFunctions *QGLScreen::surfaceFunctions() const
{
    return d_ptr->functions;
}

/*!
    \since 4.4.2

    Sets the surface functions object for this QGLScreen to \a functions.
    The QGLScreen will take over ownership of \a functions and delete
    it when the QGLScreen is deleted.

    \sa setSurfaceFunctions()
*/
void QGLScreen::setSurfaceFunctions(QGLScreenSurfaceFunctions *functions)
{
    if (functions && functions != d_ptr->functions) {
        delete d_ptr->functions;
        d_ptr->functions = functions;
    }
}

/*!
    \internal
    \preliminary
    \class QGLScreenSurfaceFunctions
    \brief The QGLScreenSurfaceFunctions class encapsulates the functions for creating native windows and pixmaps for OpenGL ES.
*/

/*!
    \since 4.4.2

    Creates a native OpenGLES drawable for the surface of \a widget and
    returns it in \a native.  Returns true if the OpenGLES drawable could
    be created, or false if windows are not supported.

    This function will be called if the NativeWindows option is set on
    the screen.

    \sa createNativePixmap(), createNativeImage(), QGLScreen::options()
*/
bool QGLScreenSurfaceFunctions::createNativeWindow(QWidget *widget, NativeWindowType *native)
{
    Q_UNUSED(widget);
    Q_UNUSED(native);
    return false;
}

/*!
    \since 4.4.2

    Creates a native OpenGLES drawable for directly rendering into
    \a pixmap and returns it in \a native.  Returns true if the OpenGLES
    drawable could be created, or false if direct rendering into pixmaps
    is not supported.

    This function will be called if the NativePixmaps option is set on
    the screen.

    \sa createNativeWindow(), createNativeImage(), QGLScreen::options()
*/
bool QGLScreenSurfaceFunctions::createNativePixmap(QPixmap *pixmap, NativePixmapType *native)
{
    Q_UNUSED(pixmap);
    Q_UNUSED(native);
    return false;
}

/*!
    \since 4.4.2

    Creates a native OpenGLES drawable for directly rendering into
    \a image and returns it in \a native.  Returns true if the OpenGLES
    drawable could be created, or false if direct rendering into images
    is not supported.

    This function will be called if the NativeImages option is set on
    the screen.

    \sa createNativeWindow(), createNativePixmap(), QGLScreen::options()
*/
bool QGLScreenSurfaceFunctions::createNativeImage(QImage *image, NativePixmapType *native)
{
    Q_UNUSED(image);
    Q_UNUSED(native);
    return false;
}

QT_END_NAMESPACE
