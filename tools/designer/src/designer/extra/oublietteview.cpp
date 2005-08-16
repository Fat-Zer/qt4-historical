/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#include <QtGui/QScrollBar>
#include "oubliette.h"
#include "oublietteview.h"


OublietteView::OublietteView()
{
    m_oubliette = new Oubliette;
    setWidget(m_oubliette);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    connect(m_oubliette, SIGNAL(characterMoved(const QPoint &)),
            this, SLOT(scrollToCharacter(const QPoint &)));
    setFocusPolicy(Qt::NoFocus);
    m_oubliette->setFocus();
    scrollToCharacter(m_oubliette->visualCursorPos());
}

OublietteView::~OublietteView()
{
}

void OublietteView::scrollToCharacter(const QPoint &pt)
{
    bool needUpdate = false;
    if (qAbs(pt.x() - horizontalScrollBar()->value()) >= 10 * 32) {
        horizontalScrollBar()->setValue(pt.x() - width() / 2);
        needUpdate = true;
    }
    if (qAbs(pt.y() - (verticalScrollBar()->value())) >= 6 * 32) {
        verticalScrollBar()->setValue(pt.y() - height() / 2);
        needUpdate = true;
    }
    if (needUpdate)
        scrollContentsBy(0, 0);
}
