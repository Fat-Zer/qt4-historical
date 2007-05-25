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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#include <QPixmap>

class DemoTextItem;
class ImageItem;

class MainWindow : public QGraphicsView
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void enableMask(bool enable);
    void toggleFullscreen();
    int performBenchmark();    
    void switchTimerOnOff(bool on);
    void start();
    
    QGraphicsScene *scene;
    bool loop;

    // FPS stuff:
    QList<QTime> frameTimeList;
    QList<float> fpsHistory;
    float currentFps;
    float fpsMedian;
    DemoTextItem *fpsLabel;

protected:
    // Overidden methods:
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawItems(QPainter *painter, int numItems, QGraphicsItem ** items, const QStyleOptionGraphicsItem* options);
    
private slots:
    void tick();

private:
    void setupWidget();
    void setupSceneItems();
    void drawBackgroundToPixmap();
    void setupScene();
    bool measureFps();
    void forceFpsMedianCalculation();
    void checkAdapt();
    QTimer updateTimer;
    QTime demoStartTime;
    QTime fpsTime;
    QPixmap background;
    ImageItem *trolltechLogo;
    ImageItem *qtLogo;
    bool doneAdapt;
};

#endif // MAIN_WINDOW_H

