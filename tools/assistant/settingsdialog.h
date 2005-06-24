/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the assistant application of the Qt Toolkit.
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

#ifndef SETTINGSDIALOGIMPL_H
#define SETTINGSDIALOGIMPL_H

#include "ui_settingsdialog.h"

#include <qdialog.h>
#include <qstringlist.h>

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent);

    inline QComboBox *fontCombo() const
    { return ui.fontCombo; }

    inline QComboBox *fixedFontCombo() const
    { return ui.fixedfontCombo; }

    inline QCheckBox *linkUnderlineCB() const
    { return ui.linkUnderlineCB; }

    inline QToolButton *colorButton() const
    { return ui.colorButton; }

    inline QTabWidget *settingsTab() const
    { return ui.settingsTab; }


private slots:
    void on_buttonOk_clicked();
    void on_buttonCancel_clicked();
    void on_colorButton_clicked();
    void on_buttonBrowse_clicked();
    void on_buttonHome_clicked();
    void on_buttonPDF_clicked();

    void init();
    void accept();
    void reject();

private:
    void setFile(QLineEdit *le, const QString &caption);

private:
    Ui::SettingsDialog ui;
};

#endif
