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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "ui_settingsdialog.h"

#include <QDialog>
#include <QStringList>

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent);

    inline QTabWidget *settingsTab() const
    { return ui.settingsTab; }


private slots:
    void on_buttonOk_clicked();
    void on_buttonCancel_clicked();
    void on_buttonBrowse_clicked();
    void on_buttonHome_clicked();
    void on_buttonPDF_clicked();

    void init();
    
private:
    void setFile(QLineEdit *le, const QString &caption);

private:
    Ui::SettingsDialog ui;
};

#endif // SETTINGSDIALOG_H
