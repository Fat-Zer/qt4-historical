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

#ifndef QLAYOUTENGINE_P_H
#define QLAYOUTENGINE_P_H

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

#include "QtGui/qlayoutitem.h"

template <typename T> class QVector;

struct QLayoutStruct
{
    inline void init(int stretchFactor = 0, int spacing = 0) {
        stretch = stretchFactor;
        minimumSize = sizeHint = spacing;
        maximumSize = QLAYOUTSIZE_MAX;
        expansive = false;
        empty = true;
    }

    int smartSizeHint() {
        return (stretch > 0) ? minimumSize : sizeHint;
    }

    // parameters
    int stretch;
    int sizeHint;
    int maximumSize;
    int minimumSize;
    bool expansive;
    bool empty;

    // temporary storage
    bool done;

    // result
    int pos;
    int size;
};


Q_GUI_EXPORT void qGeomCalc(QVector<QLayoutStruct> &chain, int start, int count,
                         int pos, int space, int spacer);
Q_GUI_EXPORT QSize qSmartMinSize(const QWidgetItem *i);
Q_GUI_EXPORT QSize qSmartMinSize(const QWidget *w);
Q_GUI_EXPORT QSize qSmartMaxSize(const QWidgetItem *i, Qt::Alignment align = 0);
Q_GUI_EXPORT QSize qSmartMaxSize(const QWidget *w, Qt::Alignment align = 0);


/*
  Modify total maximum (max) and total expansion (exp)
  when adding boxmax/boxexp.

  Expansive boxes win over non-expansive boxes.
*/
static inline void qMaxExpCalc(int & max, bool &exp,
                               int boxmax, bool boxexp)
{
    if (exp) {
        if (boxexp)
            max = qMax(max, boxmax);
    } else {
        if (boxexp)
            max = boxmax;
        else
            max = qMin(max, boxmax);
    }
    exp = exp || boxexp;
}

#endif // QLAYOUTENGINE_P_H
