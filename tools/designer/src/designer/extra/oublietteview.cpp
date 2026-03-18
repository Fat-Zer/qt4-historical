/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
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
    connect(m_oubliette, SIGNAL(characterMoved(QPoint)),
            this, SLOT(scrollToCharacter(QPoint)));
    setFocusPolicy(Qt::NoFocus);
    m_oubliette->setFocus();
    scrollToCharacter(m_oubliette->visualCursorPos());
}

OublietteView::~OublietteView()
{
}

void OublietteView::scrollToCharacter(const QPoint &pt)
{
    if (qAbs(pt.x() - horizontalScrollBar()->value()) >= 10 * 32)
        horizontalScrollBar()->setValue(pt.x() - width() / 2);

    if (qAbs(pt.y() - (verticalScrollBar()->value())) >= 6 * 32)
        verticalScrollBar()->setValue(pt.y() - height() / 2);

}
