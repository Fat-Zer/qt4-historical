/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#include "qsizegrip.h"

#ifndef QT_NO_SIZEGRIP

#include "qapplication.h"
#include "qevent.h"
#include "qpainter.h"
#include "qstyle.h"
#include "qstyleoption.h"

#if defined(Q_WS_X11)
#include <private/qt_x11_p.h>
#elif defined (Q_WS_WIN)
#include "qt_windows.h"
#endif

#include <private/qwidget_p.h>

class QSizeGripPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QSizeGrip)
public:
    void init();
    QPoint p;
    QRect r;
    int d;
    bool hiddenByUser;
};

static QWidget *qt_sizegrip_topLevelWidget(QWidget* w)
{
    while (!w->isWindow() && !(w->parentWidget()->windowType() == Qt::SubWindow))
        w = w->parentWidget();
    return w;
}


/*!
    \class QSizeGrip

    \brief The QSizeGrip class provides a corner-grip for resizing a top-level window.

    \ingroup application
    \ingroup basic
    \ingroup appearance

    This widget works like the standard Windows resize handle. In the
    X11 version this resize handle generally works differently from
    the one provided by the system; we hope to reduce this difference
    in the future.

    Put this widget anywhere in a widget tree and the user can use it
    to resize the top-level window. Generally, this should be in the
    lower right-hand corner. Note that QStatusBar already uses this
    widget, so if you have a status bar (e.g. you are using
    QMainWindow), then you don't need to use this widget explicitly.

    On some platforms the sizegrip automatically hides itself when the
    window is shown full screen or maximised.

    \table 50%
    \row \o \inlineimage plastique-sizegrip.png Screenshot of a Plastique style size grip
    \o A size grip widget at the bottom-right corner of a main window, shown in the
    \l{Plastique Style Widget Gallery}{Plastique widget style}.
    \endtable

    The QSizeGrip class inherits QWidget and reimplements the \l
    {QWidget::mousePressEvent()}{mousePressEvent()} and \l
    {QWidget::mouseMoveEvent()}{mouseMoveEvent()} functions to feature
    the resize functionality, and the \l
    {QWidget::paintEvent()}{paintEvent()} function to render the
    sizegrip widget.

    \sa QStatusBar QWidget::windowState()
*/


/*!
    Constructs a resize corner as a child widget of  the given \a
    parent.
*/
QSizeGrip::QSizeGrip(QWidget * parent)
    : QWidget(*new QSizeGripPrivate, parent, 0)
{
    Q_D(QSizeGrip);
    d->init();
}

#ifdef QT3_SUPPORT
/*!
    \obsolete

    Constructs a resize corner with the given \a name, as a child
    widget of the given \a parent.
*/
QSizeGrip::QSizeGrip(QWidget * parent, const char* name)
    : QWidget(*new QSizeGripPrivate, parent, 0)
{
    Q_D(QSizeGrip);
    setObjectName(QString::fromAscii(name));
    d->init();
}
#endif

void QSizeGripPrivate::init()
{
    Q_Q(QSizeGrip);
    hiddenByUser = false;
#ifndef QT_NO_CURSOR
#ifndef Q_WS_MAC
    q->setCursor(q->isRightToLeft() ? Qt::SizeBDiagCursor : Qt::SizeFDiagCursor);
#endif
#endif
    q->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));
#if defined(Q_WS_X11)
    if (qt_sizegrip_topLevelWidget(q)->isWindow()) {
        WId id = q->winId();
        XChangeProperty(X11->display, q->window()->winId(),
                        ATOM(_QT_SIZEGRIP), XA_WINDOW, 32, PropModeReplace,
                        (unsigned char *)&id, 1);
    }
#endif
    QWidget *tlw = qt_sizegrip_topLevelWidget(q);
    tlw->installEventFilter(q);
}


/*!
    Destroys this size grip.
*/
QSizeGrip::~QSizeGrip()
{
#if defined(Q_WS_X11)
    if (!QApplication::closingDown() && parentWidget()) {
        WId id = XNone;
        XChangeProperty(X11->display, window()->winId(),
                        ATOM(_QT_SIZEGRIP), XA_WINDOW, 32, PropModeReplace,
                        (unsigned char *)&id, 1);
    }
#endif
}

/*!
  \reimp
*/
QSize QSizeGrip::sizeHint() const
{
    QStyleOption opt(0);
    opt.init(this);
    return (style()->sizeFromContents(QStyle::CT_SizeGrip, &opt, QSize(13, 13), this).
            expandedTo(QApplication::globalStrut()));
}

/*!
    Paints the resize grip.

    Resize grips are usually rendered as small diagonal textured lines
    in the lower-right corner. The paint event is passed in the \a
    event parameter.
*/
void QSizeGrip::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QStyleOption opt(0);
    opt.init(this);
    style()->drawControl(QStyle::CE_SizeGrip, &opt, &painter, this);
}

/*!
    \fn void QSizeGrip::mousePressEvent(QMouseEvent * event)

    Receives the mouse press events for the widget, and primes the
    resize operation. The mouse press event is passed in the \a event
    parameter.
*/
void QSizeGrip::mousePressEvent(QMouseEvent * e)
{
    Q_D(QSizeGrip);
    d->p = e->globalPos();
    d->r = qt_sizegrip_topLevelWidget(this)->geometry();
}


/*!
    \fn void QSizeGrip::mouseMoveEvent(QMouseEvent * event)
    Resizes the top-level widget containing this widget. The mouse
    move event is passed in the \a event parameter.
*/
void QSizeGrip::mouseMoveEvent(QMouseEvent * e)
{
    if (e->buttons() != Qt::LeftButton)
        return;

    Q_D(QSizeGrip);
    QWidget* tlw = qt_sizegrip_topLevelWidget(this);
    if (tlw->testAttribute(Qt::WA_WState_ConfigPending))
        return;

    QPoint np(e->globalPos());

    if (!tlw->isWindow()) {
        QWidget* ws = tlw->parentWidget()->parentWidget();
        QPoint tmp(ws->mapFromGlobal(np));
        if (tmp.x() > ws->width())
            tmp.setX(ws->width());
        if (tmp.y() > ws->height())
            tmp.setY(ws->height());
        np = ws->mapToGlobal(tmp);
    }

    int w;
    int h = np.y() - d->p.y() + d->r.height();

    if (isRightToLeft())
        w = d->r.width() - (np.x() - d->p.x());
    else
        w = np.x() - d->p.x() + d->r.width();

    if (w < 1)
        w = 1;
    if (h < 1)
        h = 1;
    QSize ms(tlw->minimumSize());
    ms = ms.expandedTo(minimumSize());
    if (w < ms.width())
        w = ms.width();
    if (h < ms.height())
        h = ms.height();

    if (isRightToLeft()) {
        QRect r(0, 0, w, h);
        r.moveTopRight(d->r.topRight());
        tlw->setGeometry(r);
    } else {
        tlw->resize(w, h);
    }

#ifdef Q_WS_WIN
    MSG msg;
    while(PeekMessage(&msg, winId(), WM_MOUSEMOVE, WM_MOUSEMOVE, PM_REMOVE))
      ;
#endif
}

/*! \reimp */
void QSizeGrip::setVisible(bool visible)
{
    Q_D(QSizeGrip);
    d->hiddenByUser = !visible;
    QWidget::setVisible(visible);
}


/*! \reimp */
bool QSizeGrip::eventFilter(QObject *o, QEvent *e)
{
    Q_D(QSizeGrip);
    QWidget *tlw = qt_sizegrip_topLevelWidget(this);
    if (!d->hiddenByUser && e->type() == QEvent::WindowStateChange && o == tlw) {
        QWidget::setVisible((tlw->windowState() &
                             (Qt::WindowFullScreen
#ifndef Q_WS_MAC
                              | Qt::WindowMaximized
#endif
                              ))==0);
    }
    return false;
}

/*! \reimp */
bool QSizeGrip::event(QEvent *e)
{
#if defined(Q_WS_MAC)
    switch(e->type()) {
    case QEvent::Hide:
    case QEvent::Show:
        if(!QApplication::closingDown() && parentWidget()) {
            if(QWidget *w = qt_sizegrip_topLevelWidget(this)) {
                if(w->isWindow())
                    QWidgetPrivate::qt_mac_update_sizer(w, e->type() == QEvent::Hide ? -1 : 1);
            }
        }
        break;
    default:
        break;
    }
#endif
    return QWidget::event(e);
}

#endif //QT_NO_SIZEGRIP
