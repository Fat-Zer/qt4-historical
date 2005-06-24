/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QVIEWPORT_P_H
#define QVIEWPORT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <private/qframe_p.h>

class QScrollBar;
class QAbstractScrollAreaPrivate: public QFramePrivate
{
    Q_DECLARE_PUBLIC(QAbstractScrollArea)

public:
    QAbstractScrollAreaPrivate();
    QScrollBar *hbar, *vbar;
    Qt::ScrollBarPolicy vbarpolicy, hbarpolicy;

    QWidget *viewport;
    int left, top, right, bottom; // viewport margin

    int xoffset, yoffset;

    void init();
    void layoutChildren();
    bool viewportEvent(QEvent *);

    void hslide(int);
    void vslide(int);
    void showOrHideScrollBars();
};

#endif // QVIEWPORT_P_H
