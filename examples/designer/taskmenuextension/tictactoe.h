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

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>

class QSize;
class QRect;

class TicTacToe : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state WRITE setState)
public:
    TicTacToe(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setState(const QString &newState);
    QString state() const;
    void clearBoard();

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    enum {Empty = '-', Cross = 'X', Nought = 'O' };

    QRect cellRect(int row, int col) const;
    int cellWidth() const {return width()/ 3;}
    int cellHeight() const {return height()/ 3;}

    QString myState;
    int turnNumber;
};

#endif
