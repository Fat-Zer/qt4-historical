/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
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

#ifndef SIMPLEWIZARD_H
#define SIMPLEWIZARD_H

#include <QDialog>
#include <QList>

class QHBoxLayout;
class QPushButton;
class QVBoxLayout;

class SimpleWizard : public QDialog
{
    Q_OBJECT

public:
    SimpleWizard(QWidget *parent = 0);

    void setButtonEnabled(bool enable);

protected:
    virtual QWidget *createPage(int index) = 0;
    void setNumPages(int n);

private slots:
    void backButtonClicked();
    void nextButtonClicked();

private:
    void switchPage(QWidget *oldPage);

    QList<QWidget *> history;
    int numPages;
    QPushButton *cancelButton;
    QPushButton *backButton;
    QPushButton *nextButton;
    QPushButton *finishButton;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
};

#endif
