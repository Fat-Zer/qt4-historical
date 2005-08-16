/****************************************************************************
**
** Copyright (C) 2006-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>

#include "mainwindow.h"
#include "stylesheeteditor.h"

MainWindow::MainWindow()
{
    ui.setupUi(this);

    ui.nameLabel->setProperty("class", "mandatory QLabel");

    styleSheetEditor = new StyleSheetEditor(this);

    statusBar()->addWidget(new QLabel(tr("Ready")));

    connect(ui.exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui.aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::on_editStyleAction_triggered()
{
    styleSheetEditor->show();
    styleSheetEditor->activateWindow();
}

void MainWindow::on_aboutAction_triggered()
{
    QMessageBox::about(this, tr("About Style sheet"),
        tr("The <b>Style Sheet</b> example shows how widgets can be styled "
           "using <a href=\"http://doc.trolltech.com/4.2/stylesheet.html\">Qt "
           "Style Sheets</a>. Click <b>File|Edit Style Sheet</b> to pop up the "
           "style editor, and either choose an existing style sheet or design "
           "your own."));
}
