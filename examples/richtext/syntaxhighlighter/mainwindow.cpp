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

#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupEditor();

    setCentralWidget(editor);
    setWindowTitle(tr("Syntax Highlighter"));
}

void MainWindow::newFile()
{
    editor->clear();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this,
            tr("Open File"), "", "qmake Files (*.pro *.prf *.pri)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            editor->setPlainText(file.readAll());
    }
}

void MainWindow::setupEditor()
{
    QTextCharFormat defaultFormat;
    defaultFormat.setFontFamily("Courier");
    defaultFormat.setFontPointSize(10);

    QTextCharFormat variableFormat = defaultFormat;
    variableFormat.setFontWeight(QFont::Bold);
    variableFormat.setForeground(Qt::blue);
    highlighter.addMapping("\\b[A-Z_]+\\b", variableFormat);

    QTextCharFormat singleLineCommentFormat = defaultFormat;
    singleLineCommentFormat.setBackground(QColor("#77ff77"));
    highlighter.addMapping("#[^\n]*", singleLineCommentFormat);

    QTextCharFormat quotationFormat = defaultFormat;
    quotationFormat.setBackground(Qt::cyan);
    quotationFormat.setForeground(Qt::blue);
    highlighter.addMapping("\".*\"", quotationFormat);

    QTextCharFormat functionFormat = defaultFormat;
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    highlighter.addMapping("\\b[a-z0-9_]+\\(.*\\)", functionFormat);

    editor = new QTextEdit;
    editor->setFont(defaultFormat.font());
    editor->document()->setDefaultFont(defaultFormat.font());
    highlighter.addToDocument(editor->document());
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&New..."), this, SLOT(newFile()),
                        QKeySequence(tr("Ctrl+N", "File|New")));
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()),
                        QKeySequence(tr("Ctrl+O", "File|Open")));
    fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()),
                        QKeySequence(tr("Ctrl+Q", "File|Exit")));
}
