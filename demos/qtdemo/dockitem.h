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

#ifndef DOCK_ITEM_H
#define DOCK_ITEM_H

#include <QtGui>
#include "demoitem.h"

class DockItem : public DemoItem
{
public:
    enum ORIENTATION {UP, DOWN, LEFT, RIGHT};
    
    DockItem(ORIENTATION orien, qreal x, qreal y, qreal width, qreal length, QGraphicsScene *scene = 0, QGraphicsItem *parent = 0);
    virtual ~DockItem();
    
    virtual QRectF boundingRect() const; // overridden
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0); // overridden
    
    qreal length;
    qreal width;
    ORIENTATION orientation;
    
private:
    void setupPixmap();
    QPixmap *pixmap;
};

#endif // DOCK_ITEM_H

