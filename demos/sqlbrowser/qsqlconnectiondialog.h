/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#ifndef QSQLCONNECTIONDIALOG_H
#define QSQLCONNECTIONDIALOG_H

#include <qdialog.h>
#include <qmessagebox.h>

#include "ui_qsqlconnectiondialog.h"

class QSqlConnectionDialog: public QDialog
{
    Q_OBJECT
public:
    QSqlConnectionDialog(QWidget *parent = 0);
    ~QSqlConnectionDialog();

    QString driverName() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString hostName() const;
    int port() const;
    bool useInMemoryDatabase() const;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked() { reject(); }
    void on_dbCheckBox_clicked() { ui.connGroupBox->setEnabled(!ui.dbCheckBox->isChecked()); }

private:
    Ui::QSqlConnectionDialogUi ui;
};

#endif
