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
** Definition of GameBoard class, Qt tutorial 13
**
****************************************************************/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>

class QLCDNumber;
class CannonField;

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    GameBoard(QWidget *parent = 0);

protected slots:
    void fire();
    void hit();
    void missed();
    void newGame();

private:
    QLCDNumber *hits;
    QLCDNumber *shotsLeft;
    CannonField *cannonField;
};

#endif // GAMEBOARD_H
