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

#include <QtGui>

#include "characterwidget.h"
#include "mainwindow.h"

MainWindow::MainWindow()
{
    QWidget *centralWidget = new QWidget;

    QLabel *fontLabel = new QLabel(tr("Font:"));
    fontCombo = new QComboBox;
    QLabel *styleLabel = new QLabel(tr("Style:"));
    styleCombo = new QComboBox;

    scrollArea = new QScrollArea;
    characterWidget = new CharacterWidget;
    scrollArea->setWidget(characterWidget);

    findFonts();
    findStyles();

    lineEdit = new QLineEdit;
    QPushButton *clipboardButton = new QPushButton(tr("&To clipboard"));

    clipboard = QApplication::clipboard();

    connect(fontCombo, SIGNAL(activated(const QString &)),
            this, SLOT(findStyles()));
    connect(fontCombo, SIGNAL(activated(const QString &)),
            characterWidget, SLOT(updateFont(const QString &)));
    connect(styleCombo, SIGNAL(activated(const QString &)),
            characterWidget, SLOT(updateStyle(const QString &)));
    connect(characterWidget, SIGNAL(characterSelected(const QString &)),
            this, SLOT(insertCharacter(const QString &)));
    connect(clipboardButton, SIGNAL(clicked()), this, SLOT(updateClipboard()));

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(fontLabel);
    controlsLayout->addWidget(fontCombo, 1);
    controlsLayout->addWidget(styleLabel);
    controlsLayout->addWidget(styleCombo, 1);
    controlsLayout->addStretch(1);

    QHBoxLayout *lineLayout = new QHBoxLayout;
    lineLayout->addWidget(lineEdit, 1);
    lineLayout->addSpacing(12);
    lineLayout->addWidget(clipboardButton);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(controlsLayout);
    centralLayout->addWidget(scrollArea, 1);
    centralLayout->addSpacing(4);
    centralLayout->addLayout(lineLayout);
    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Character Map"));
}

void MainWindow::findFonts()
{
    QFontDatabase fontDatabase;
    fontCombo->clear();

    QString family;
    foreach (family, fontDatabase.families())
        fontCombo->addItem(family);
}

void MainWindow::findStyles()
{
    QFontDatabase fontDatabase;
    QString currentItem = styleCombo->currentText();
    styleCombo->clear();

    QString style;
    foreach (style, fontDatabase.styles(fontCombo->currentText()))
        styleCombo->addItem(style);

    if (styleCombo->findText(currentItem) == -1)
        styleCombo->setCurrentIndex(0);
}

void MainWindow::insertCharacter(const QString &character)
{
    lineEdit->insert(character);
}

void MainWindow::updateClipboard()
{
    clipboard->setText(lineEdit->text(), QClipboard::Clipboard);
    clipboard->setText(lineEdit->text(), QClipboard::Selection);
}
