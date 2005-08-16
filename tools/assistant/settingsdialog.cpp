/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the Qt Assistant of the Qt Toolkit.
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

#include "settingsdialog.h"
#include "docuparser.h"
#include "config.h"

#include <QApplication>
#include <QPushButton>
#include <QCheckBox>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <QToolButton>
#include <QTabWidget>
#include <QMap>
#include <QFontDatabase>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    init();
}

void SettingsDialog::init()
{
    Config *config = Config::configuration();

    ui.browserApp->setText(config->webBrowser());
    ui.homePage->setText(config->homePage());
    ui.pdfApp->setText(config->pdfReader());
}

void SettingsDialog::on_buttonBrowse_clicked()
{
    setFile(ui.browserApp, tr("Qt Assistant - Set Web Browser"));
}

void SettingsDialog::on_buttonPDF_clicked()
{
    setFile(ui.pdfApp, tr("Qt Assistant - Set PDF Browser"));
}

void SettingsDialog::on_buttonHome_clicked()
{
    setFile(ui.homePage, tr("Qt Assistant - Set Homepage"));
}

void SettingsDialog::setFile(QLineEdit *le, const QString &caption)
{
    QString fileName = QFileDialog::getOpenFileName(this, caption);
    if (!fileName.isEmpty())
        le->setText(fileName);    
}

void SettingsDialog::on_buttonOk_clicked()
{
    Config *config = Config::configuration();
    config->setWebBrowser(ui.browserApp->text());
    config->setHomePage(ui.homePage->text());
    config->setPdfReader(ui.pdfApp->text());
    accept();
}

void SettingsDialog::on_buttonCancel_clicked()
{
    reject();
}
