/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "qpf2.h"

class QListWidgetItem;

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow(const QString &customFont);

private Q_SLOTS:
    void on_actionAdd_Custom_Font_triggered();
    void on_selectAll_clicked();
    void on_deselectAll_clicked();
    void on_invertSelection_clicked();
    void fontChanged();
    void on_browsePath_clicked();
    void on_browseSampleFile_clicked();
    void on_generate_clicked();
    void on_sampleFile_editingFinished();

private:
    void populateCharacterRanges();
    void addCustomFont(const QString &fontFile);

private:
    QList<QPF::CharacterRange> sampleFileRanges;
};

#endif // MAINWINDOW_H
