/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the qtconfig application of the Qt Toolkit.
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

#include "previewwidget.h"
#include <qevent.h>

PreviewWidget::PreviewWidget( QWidget *parent, const char *name )
    : PreviewWidgetBase( parent, name )
{
    // install event filter on child widgets
    QObjectList l = queryList("QWidget");
    for (int i = 0; i < l.size(); ++i) {
        QObject * obj = l.at(i);
        obj->installEventFilter(this);
        ((QWidget*)obj)->setFocusPolicy(Qt::NoFocus);
    }
}


void PreviewWidget::closeEvent(QCloseEvent *e)
{
    e->ignore();
}


bool PreviewWidget::eventFilter(QObject *, QEvent *e)
{
    switch ( e->type() ) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseMove:
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::Enter:
    case QEvent::Leave:
        return true; // ignore;
    default:
        break;
    }
    return false;
}
