/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>

#include "printpanel.h"

PrintPanel::PrintPanel(QWidget *parent)
    : QWidget(parent)
{
/*
    QLabel *label = new QLabel(tr("<b>TROLL PRINT</b>"));
    label->setAlignment(Qt::AlignCenter);
*/

    twoSidedGroupBox = new QGroupBox(tr("2-sided"));
    twoSidedEnabledRadio = new QRadioButton(tr("Enabled"));
    twoSidedDisabledRadio = new QRadioButton(tr("Disabled"));
    twoSidedDisabledRadio->setChecked(true);

    colorsGroupBox = new QGroupBox(tr("Colors"));
    colorsEnabledRadio = new QRadioButton(tr("Enabled"));
    colorsDisabledRadio = new QRadioButton(tr("Disabled"));
    colorsDisabledRadio->setChecked(true);

    QHBoxLayout *twoSidedLayout = new QHBoxLayout;
    twoSidedLayout->addWidget(twoSidedEnabledRadio);
    twoSidedLayout->addWidget(twoSidedDisabledRadio);
    twoSidedGroupBox->setLayout(twoSidedLayout);

    QHBoxLayout *colorsLayout = new QHBoxLayout;
    colorsLayout->addWidget(colorsEnabledRadio);
    colorsLayout->addWidget(colorsDisabledRadio);
    colorsGroupBox->setLayout(colorsLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
/*
    mainLayout->addWidget(label);
*/
    mainLayout->addWidget(twoSidedGroupBox);
    mainLayout->addWidget(colorsGroupBox);
    setLayout(mainLayout);
}
