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

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>

class QLineEdit;
class Button;

class Calculator : public QDialog
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *target, QEvent *event);

private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();

private:
    Button *createButton(const QString &text, const QColor &color,
                         const char *member);
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);

    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;

    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];

    Button *pointButton;
    Button *changeSignButton;
    Button *backspaceButton;
    Button *clearButton;
    Button *clearAllButton;
    Button *clearMemoryButton;
    Button *readMemoryButton;
    Button *setMemoryButton;
    Button *addToMemoryButton;
   
    Button *divisionButton;
    Button *timesButton;
    Button *minusButton;
    Button *plusButton;
    Button *squareRootButton;
    Button *powerButton;
    Button *reciprocalButton;
    Button *equalButton;
};

#endif
