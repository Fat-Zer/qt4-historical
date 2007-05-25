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

#ifndef DEMO_ITEM_ANIMATION_H
#define DEMO_ITEM_ANIMATION_H

#include <QtCore>
#include <QtGui>

class DemoItem;

class DemoItemAnimation : public QGraphicsItemAnimation
{
    Q_OBJECT
    
public:
    enum INOROUT {ANIM_IN, ANIM_OUT, ANIM_UNSPECIFIED};
    
    DemoItemAnimation(DemoItem *item, INOROUT inOrOut = ANIM_UNSPECIFIED);
    virtual ~DemoItemAnimation();
    
    virtual void play(bool fromStart = true, bool force = false);
    virtual void playReverse();
    virtual void stop(bool reset = true);
    virtual void setRepeat(int nr = 0);
    
    void setDuration(int duration);
    void setDuration(float duration){ setDuration(int(duration)); };
    void setOpacityAt0(qreal opacity);
    void setOpacityAt1(qreal opacity);
    void setOpacity(qreal step);
    void setCurrentTime(int ms);
    void setStartPos(const QPointF &pos);
    bool notOwnerOfItem();
    
    bool running();
    bool runningOrItemLocked();
    void lockItem(bool state);
    void prepare();
    
    DemoItem *demoItem();
    
    virtual void afterAnimationStep(qreal step); // overridden
    
    QTimeLine *timeline;
    qreal opacityAt0;
    qreal opacityAt1;
    int startDelay;
    QPointF startPos;
    bool hideOnFinished;
    bool moveOnPlay;
    bool forcePlay;
    bool fromStart;
    INOROUT inOrOut;

public slots:
    virtual void playWithoutDelay();
};

#endif // DEMO_ITEM_ANIMATION_H



