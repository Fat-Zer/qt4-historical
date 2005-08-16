/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
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

#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H

#include "simplewizard.h"

class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class FirstPage;
class SecondPage;
class ThirdPage;

class ClassWizard : public SimpleWizard
{
    Q_OBJECT

public:
    ClassWizard(QWidget *parent = 0);

protected:
    QWidget *createPage(int index);
    void accept();

private:
    FirstPage *firstPage;
    SecondPage *secondPage;
    ThirdPage *thirdPage;

    friend class FirstPage;
    friend class SecondPage;
    friend class ThirdPage;
};

class FirstPage : public QWidget
{
    Q_OBJECT

public:
    FirstPage(ClassWizard *wizard);

private slots:
    void classNameChanged();

private:
    QLabel *topLabel;
    QLabel *classNameLabel;
    QLabel *baseClassLabel;
    QLineEdit *classNameLineEdit;
    QLineEdit *baseClassLineEdit;
    QCheckBox *qobjectMacroCheckBox;
    QGroupBox *groupBox;
    QRadioButton *qobjectCtorRadioButton;
    QRadioButton *qwidgetCtorRadioButton;
    QRadioButton *defaultCtorRadioButton;
    QCheckBox *copyCtorCheckBox;

    friend class ClassWizard;
    friend class SecondPage;
    friend class ThirdPage;
};

class SecondPage : public QWidget
{
    Q_OBJECT

public:
    SecondPage(ClassWizard *wizard);

private:
    QLabel *topLabel;
    QCheckBox *commentCheckBox;
    QCheckBox *protectCheckBox;
    QCheckBox *includeBaseCheckBox;
    QLabel *macroNameLabel;
    QLabel *baseIncludeLabel;
    QLineEdit *macroNameLineEdit;
    QLineEdit *baseIncludeLineEdit;

    friend class ClassWizard;
};

class ThirdPage : public QWidget
{
    Q_OBJECT

public:    
    ThirdPage(ClassWizard *wizard);

private:
    QLabel *topLabel;
    QLabel *outputDirLabel;
    QLabel *headerLabel;
    QLabel *implementationLabel;
    QLineEdit *outputDirLineEdit;
    QLineEdit *headerLineEdit;
    QLineEdit *implementationLineEdit;

    friend class ClassWizard;
};

#endif
