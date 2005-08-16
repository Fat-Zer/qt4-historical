/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

/****************************************************************
**
** Definition of CannonField class, Qt tutorial 14
**
****************************************************************/

#ifndef CANNON_H
#define CANNON_H

#include <QWidget>

class QTimer;

class CannonField : public QWidget
{
    Q_OBJECT

public:
    CannonField(QWidget *parent = 0);

    int angle() const { return currentAngle; }
    int force() const { return currentForce; }
    bool gameOver() const { return gameEnded; }
    bool isShooting() const;
    QSize sizeHint() const;

public slots:
    void setAngle(int angle);
    void setForce(int force);
    void shoot();
    void newTarget();
    void setGameOver();
    void restartGame();

private slots:
    void moveShot();

signals:
    void hit();
    void missed();
    void angleChanged(int newAngle);
    void forceChanged(int newForce);
    void canShoot(bool can);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void paintShot(QPainter &painter);
    void paintTarget(QPainter &painter);
    void paintBarrier(QPainter &painter);
    void paintCannon(QPainter &painter);
    QRect cannonRect() const;
    QRect shotRect() const;
    QRect targetRect() const;
    QRect barrierRect() const;
    bool barrelHit(const QPoint &pos) const;

    int currentAngle;
    int currentForce;

    int timerCount;
    QTimer *autoShootTimer;
    float shootAngle;
    float shootForce;

    QPoint target;

    bool gameEnded;
    bool barrelPressed;
};

#endif // CANNON_H
