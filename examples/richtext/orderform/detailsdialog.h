/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#ifndef DETAILSDIALOG_H
#define DETAILSDIALOG_H

#include <QDialog>
#include <QList>
#include <QPair>
#include <QString>

class QCheckBox;
class QLineEdit;
class QTableWidget;
class QTextEdit;
class QWidget;

class DetailsDialog : public QDialog
{
    Q_OBJECT

public:
    DetailsDialog(const QString &title, QWidget *parent);

public slots:
    void verify();

public:
    QList<QPair<QString,int> > orderItems();
    QString senderName() const;
    QString senderAddress() const;
    bool sendOffers();

private:
    void setupItemsTable();

    QCheckBox *offersCheckBox;
    QLineEdit *nameEdit;
    QStringList items;
    QTableWidget *itemsTable;
    QTextEdit *addressEdit;
};

#endif
