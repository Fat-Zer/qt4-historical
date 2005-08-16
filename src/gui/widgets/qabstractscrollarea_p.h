/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
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

#ifndef QT_NO_SCROLLAREA
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

    bool vend, hend;

    void init();
    void layoutChildren();
    bool viewportEvent(QEvent *);

    void hslide(int);
    void vslide(int);
    void showOrHideScrollBars();
};
#endif // QT_NO_SCROLLAREA
#endif // QVIEWPORT_P_H
