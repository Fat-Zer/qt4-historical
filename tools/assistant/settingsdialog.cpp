/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the assistant application of the Qt Toolkit.
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

#include "settingsdialog.h"
#include "docuparser.h"
#include "config.h"

#include <qapplication.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qcolordialog.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qmessagebox.h>
#include <qsettings.h>
#include <qtimer.h>
#include <qtoolbutton.h>
#include <qtabwidget.h>
#include <qmap.h>
#include <qfontdatabase.h>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    init();
}

void SettingsDialog::init()
{
    Config *config = Config::configuration();

    QFontDatabase fonts;
    ui.fontCombo->addItems(fonts.families());
    ui.fontCombo->lineEdit()->setText(config->fontFamily());
    
    ui.fixedfontCombo->addItems(fonts.families());
    ui.fixedfontCombo->lineEdit()->setText(config->fontFixedFamily());

    QPalette pal = ui.colorButton->palette();
    pal.setColor(QPalette::Active, QPalette::Button, QColor(config->linkColor()));
    ui.colorButton->setPalette(pal);

    ui.linkUnderlineCB->setChecked(config->isLinkUnderline());

    ui.browserApp->setText(config->webBrowser());
    ui.homePage->setText(config->homePage());
    ui.pdfApp->setText(config->pdfReader());
}


void SettingsDialog::on_colorButton_clicked()
{
    QPalette pal = ui.colorButton->palette();
	QColor c = QColorDialog::getColor(pal.color(QPalette::Button), this);
	pal.setColor(QPalette::Button, c);
    ui.colorButton->setPalette(pal);
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

void SettingsDialog::accept()
{
    Config *config = Config::configuration();

    config->setFontFamily(ui.fontCombo->currentText());
    config->setFontFixedFamily(ui.fixedfontCombo->currentText());
    config->setLinkColor(ui.colorButton->palette().color(QPalette::Button).name());
    config->setLinkUnderline(ui.linkUnderlineCB->isChecked());

    config->setWebBrowser(ui.browserApp->text());
    config->setHomePage(ui.homePage->text());
    config->setPdfReader(ui.pdfApp->text());

    hide();
    done(Accepted);
}

void SettingsDialog::reject()
{
    init();
    done(Rejected);
}

void SettingsDialog::on_buttonOk_clicked()
{
    accept();
}

void SettingsDialog::on_buttonCancel_clicked()
{
    reject();
}

