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

#ifndef DEMO_TEXT_ITEM_H
#define DEMO_TEXT_ITEM_H

#include <QtGui>
#include "demoitem.h"
 
class DemoTextItem : public DemoItem
{
public:
    enum TYPE {STATIC_TEXT, DYNAMIC_TEXT};
     
    DemoTextItem(const QString &text, const QFont &font, const QColor &textColor,
        float textWidth, QGraphicsScene *scene = 0, QGraphicsItem *parent = 0, TYPE type = STATIC_TEXT, const QColor &bgColor = QColor());
    void setText(const QString &text);
    QRectF boundingRect() const; // overridden
    void animationStarted(int id = 0);
    void animationStopped(int id = 0);

protected:
    virtual QImage *createImage(const QMatrix &matrix) const; // overridden
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option = 0, QWidget *widget = 0); // overridden
    
private:
    float textWidth;
    QString text;
    QFont font;
    QColor textColor;
    QColor bgColor;
    TYPE type;
};

#endif // DEMO_TEXT_ITEM_H

