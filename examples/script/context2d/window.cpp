/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
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

#include "window.h"
#include "qcontext2dcanvas.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QDir>

static QString scriptsDir()
{
    if (QFile::exists("./scripts"))
        return "./scripts";
    return ":/scripts";
}

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    QListWidget *view = new QListWidget(this);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    canvas = new QContext2DCanvas(this);
    canvas->setFixedSize(150, 150);
    hbox->addWidget(view);
    hbox->addWidget(canvas);

    QDir dir(scriptsDir());
    QFileInfoList entries = dir.entryInfoList(QStringList() << "*.js");
    for (int i = 0; i < entries.size(); ++i)
        view->addItem(entries.at(i).fileName());
    connect(view, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
            this, SLOT(selectScript(QListWidgetItem*)));

    setWindowTitle(tr("Context 2D"));
}

void Window::selectScript(QListWidgetItem *item)
{
    QFile file(scriptsDir() + "/" + item->text());
    file.open(QIODevice::ReadOnly);
    QString contents = file.readAll();
    file.close();
    canvas->setScriptContents(contents);
}
