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

#include <private/qhiviewwidget_mac_p.h>
#include <qdebug.h>

extern HIViewRef qt_mac_hiview_for(const QWidget *w); //qwidget_mac.cpp
extern HIViewRef qt_mac_hiview_for(WindowPtr w); //qwidget_mac.cpp

QHIViewWidget::QHIViewWidget(WindowRef windowref, bool createSubs, QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    create((WId)qt_mac_hiview_for(windowref), false);
    Rect rect;
    GetWindowBounds(windowref, kWindowContentRgn, &rect);
    setGeometry(QRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top));
    if(createSubs)
        createQWidgetsFromHIViews();
}

QHIViewWidget::~QHIViewWidget()
{
}

QHIViewWidget::QHIViewWidget(HIViewRef hiviewref, bool createSubs, QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
    create((WId)hiviewref, false);
    setVisible(HIViewIsVisible(hiviewref));
    if(createSubs)
        createQWidgetsFromHIViews();
}

void QHIViewWidget::createQWidgetsFromHIViews()
{
    // Nicely walk through and make HIViewWidget out of all the children
    addViews_recursive(HIViewGetFirstSubview(qt_mac_hiview_for(this)), this);
}

void QHIViewWidget::addViews_recursive(HIViewRef child, QWidget *parent)
{
    if (!child)
        return;
    QWidget *widget = QWidget::find(WId(child));
    if(!widget)
        widget = new QHIViewWidget(child, false, parent);
    addViews_recursive(HIViewGetFirstSubview(child), widget);
    addViews_recursive(HIViewGetNextView(child), parent);
}
