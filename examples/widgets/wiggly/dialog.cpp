/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#include <QtGui>

#include "dialog.h"
#include "wigglywidget.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    WigglyWidget *wigglyWidget = new WigglyWidget;
    QLineEdit *lineEdit = new QLineEdit;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(wigglyWidget);
    layout->addWidget(lineEdit);
    setLayout(layout);

    connect(lineEdit, SIGNAL(textChanged(QString)),
            wigglyWidget, SLOT(setText(QString)));

    lineEdit->setText(tr("Hello world!"));

    setWindowTitle(tr("Wiggly"));
    resize(360, 145);
}
