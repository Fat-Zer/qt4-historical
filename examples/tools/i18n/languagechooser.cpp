/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
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

#include "languagechooser.h"
#include "mainwindow.h"

#ifdef Q_WS_MAC
extern void qt_mac_set_menubar_merge(bool merge);
#endif

LanguageChooser::LanguageChooser(QWidget *parent)
    : QDialog(parent, Qt::WindowStaysOnTopHint)
{
    groupBox = new QGroupBox("Languages");

    QGridLayout *groupBoxLayout = new QGridLayout;

    QStringList qmFiles = findQmFiles();
    for (int i = 0; i < qmFiles.size(); ++i) {
        QCheckBox *checkBox = new QCheckBox(languageName(qmFiles[i]));
        qmFileForCheckBoxMap.insert(checkBox, qmFiles[i]);
        connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(checkBoxToggled()));
        groupBoxLayout->addWidget(checkBox, i / 2, i % 2);
    }
    groupBox->setLayout(groupBoxLayout);

    showAllButton = new QPushButton("Show All");
    hideAllButton = new QPushButton("Hide All");
    closeButton = new QPushButton("Close");
    closeButton->setDefault(true);

    connect(showAllButton, SIGNAL(clicked()), this, SLOT(showAll()));
    connect(hideAllButton, SIGNAL(clicked()), this, SLOT(hideAll()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(showAllButton);
    buttonLayout->addWidget(hideAllButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

#ifdef Q_WS_MAC
    qt_mac_set_menubar_merge(false);
#endif

    setWindowTitle("I18N");
}

bool LanguageChooser::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Close) {
        MainWindow *window = qobject_cast<MainWindow *>(object);
        if (window) {
            QCheckBox *checkBox = mainWindowForCheckBoxMap.key(window);
            if (checkBox)
                checkBox->setChecked(false);
        }
    }
    return QWidget::eventFilter(object, event);
}

void LanguageChooser::closeEvent(QCloseEvent * /* event */)
{
    qApp->quit();
}

void LanguageChooser::checkBoxToggled()
{
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(sender());
    MainWindow *window = mainWindowForCheckBoxMap[checkBox];
    if (!window) {
        QTranslator translator;
        translator.load(qmFileForCheckBoxMap[checkBox]);
        qApp->installTranslator(&translator);

        window = new MainWindow;
        window->setPalette(colorForLanguage(checkBox->text()));

        window->installEventFilter(this);
        mainWindowForCheckBoxMap.insert(checkBox, window);
    }
    window->setVisible(checkBox->isChecked());
}

void LanguageChooser::showAll()
{
    foreach (QCheckBox *checkBox, qmFileForCheckBoxMap.keys())
        checkBox->setChecked(true);
}

void LanguageChooser::hideAll()
{
    foreach (QCheckBox *checkBox, qmFileForCheckBoxMap.keys())
        checkBox->setChecked(false);
}

QStringList LanguageChooser::findQmFiles()
{
    QDir dir(":/translations");
    QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files,
                                          QDir::Name);
    QMutableStringListIterator i(fileNames);
    while (i.hasNext()) {
        i.next();
        i.setValue(dir.filePath(i.value()));
    }
    return fileNames;
}

QString LanguageChooser::languageName(const QString &qmFile)
{
    QTranslator translator;
    translator.load(qmFile);

    return translator.translate("MainWindow", "English");
}

QColor LanguageChooser::colorForLanguage(const QString &language)
{
    uint hashValue = qHash(language);
    int red = 156 + (hashValue & 0x3F);
    int green = 156 + ((hashValue >> 6) & 0x3F);
    int blue = 156 + ((hashValue >> 12) & 0x3F);
    return QColor(red, green, blue);
}
