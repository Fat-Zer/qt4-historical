/****************************************************************************
**
** Copyright (C) 2005-2006 Trolltech ASA. All rights reserved.
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

#include "tictactoe.h"
#include "tictactoeplugin.h"
#include "tictactoetaskmenu.h"

#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>

#include <QIcon>
#include <QtPlugin>

TicTacToePlugin::TicTacToePlugin(QObject *parent)
    :QObject(parent)
{
    initialized = false;
}

QString TicTacToePlugin::name() const
{
    return QString("TicTacToe");
}

QString TicTacToePlugin::group() const
{
    return QString("Display Widgets [Examples]");
}

QString TicTacToePlugin::toolTip() const
{
    return "";
}

QString TicTacToePlugin::whatsThis() const
{
    return "";
}

QString TicTacToePlugin::includeFile() const
{
    return QString("tictactoe.h");
}

QIcon TicTacToePlugin::icon() const
{
    return QIcon();
}

bool TicTacToePlugin::isContainer() const
{
    return false;
}

QWidget *TicTacToePlugin::createWidget(QWidget *parent)
{
    TicTacToe *ticTacToe = new TicTacToe(parent);
    ticTacToe->setState("-X-XO----");
    return ticTacToe;
}

bool TicTacToePlugin::isInitialized() const
{
    return initialized;
}

void TicTacToePlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (initialized)
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    Q_ASSERT(manager != 0);

    manager->registerExtensions(new TicTacToeTaskMenuFactory(manager),
                                Q_TYPEID(QDesignerTaskMenuExtension));

    initialized = true;
}

Q_EXPORT_PLUGIN2(taskmenuextension, TicTacToePlugin)
