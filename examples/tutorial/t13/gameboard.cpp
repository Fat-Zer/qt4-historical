/****************************************************************************
**
** Copyright (C) 2005-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "cannonfield.h"
#include "gameboard.h"
#include "lcdrange.h"

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton(tr("&Quit"));
    quit->setFont(QFont("Times", 18, QFont::Bold));

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    LCDRange *angle = new LCDRange(tr("ANGLE"));
    angle->setRange(5, 70);

    LCDRange *force = new LCDRange(tr("FORCE"));
    force->setRange(10, 50);

    cannonField = new CannonField;

    connect(angle, SIGNAL(valueChanged(int)),
            cannonField, SLOT(setAngle(int)));
    connect(cannonField, SIGNAL(angleChanged(int)),
            angle, SLOT(setValue(int)));

    connect(force, SIGNAL(valueChanged(int)),
            cannonField, SLOT(setForce(int)));
    connect(cannonField, SIGNAL(forceChanged(int)),
            force, SLOT(setValue(int)));

    connect(cannonField, SIGNAL(hit()),
            this, SLOT(hit()));
    connect(cannonField, SIGNAL(missed()),
            this, SLOT(missed()));

    QPushButton *shoot = new QPushButton(tr("&Shoot"));
    shoot->setFont(QFont("Times", 18, QFont::Bold));

    connect(shoot, SIGNAL(clicked()),
            this, SLOT(fire()));
    connect(cannonField, SIGNAL(canShoot(bool)),
            shoot, SLOT(setEnabled(bool)));

    QPushButton *restart = new QPushButton(tr("&New Game"));
    restart->setFont(QFont("Times", 18, QFont::Bold));

    connect(restart, SIGNAL(clicked()), this, SLOT(newGame()));

    hits = new QLCDNumber(2);
    hits->setSegmentStyle(QLCDNumber::Filled);

    shotsLeft = new QLCDNumber(2);
    shotsLeft->setSegmentStyle(QLCDNumber::Filled);

    QLabel *hitsLabel = new QLabel(tr("HITS"));
    QLabel *shotsLeftLabel = new QLabel(tr("SHOTS LEFT"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(shoot);
    topLayout->addWidget(hits);
    topLayout->addWidget(hitsLabel);
    topLayout->addWidget(shotsLeft);
    topLayout->addWidget(shotsLeftLabel);
    topLayout->addStretch(1);
    topLayout->addWidget(restart);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(angle);
    leftLayout->addWidget(force);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(quit, 0, 0);
    gridLayout->addLayout(topLayout, 0, 1);
    gridLayout->addLayout(leftLayout, 1, 0);
    gridLayout->addWidget(cannonField, 1, 1, 2, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);

    angle->setValue(60);
    force->setValue(25);
    angle->setFocus();

    newGame();
}

void GameBoard::fire()
{
    if (cannonField->gameOver() || cannonField->isShooting())
        return;
    shotsLeft->display(shotsLeft->intValue() - 1);
    cannonField->shoot();
}

void GameBoard::hit()
{
    hits->display(hits->intValue() + 1);
    if (shotsLeft->intValue() == 0)
        cannonField->setGameOver();
    else
        cannonField->newTarget();
}

void GameBoard::missed()
{
    if (shotsLeft->intValue() == 0)
        cannonField->setGameOver();
}

void GameBoard::newGame()
{
    shotsLeft->display(15);
    hits->display(0);
    cannonField->restartGame();
    cannonField->newTarget();
}
