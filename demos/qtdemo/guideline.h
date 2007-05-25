/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#ifndef GUIDELINE_H
#define GUIDELINE_H

#include "guide.h"
#include "demoitem.h"

class GuideLine : public Guide
{
public:
    GuideLine(const QLineF &line, Guide *follows = 0);
    GuideLine(const QPointF &end, Guide *follows = 0);
    
    void guide(DemoItem *item, float moveSpeed); // overridden
    QPointF startPos();
    QPointF endPos();
    float length();
    
private:
    QLineF line;
    
};

#endif // GUIDELINE_H

