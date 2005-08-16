/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#include <QtDesigner/QDesignerFormEditorInterface>

#include <QAction>

#include "tictactoetaskmenu.h"
#include "tictactoe.h"
#include "tictactoedialog.h"

TicTacToeTaskMenu::TicTacToeTaskMenu(TicTacToe *tic, QObject *parent)
    : QObject(parent)
{
    ticTacToe = tic;

    editStateAction = new QAction(tr("Edit State..."), this);
    connect(editStateAction, SIGNAL(triggered()), this, SLOT(editState()));
}

void TicTacToeTaskMenu::editState()
{
    TicTacToeDialog dialog(ticTacToe);
    dialog.exec();
}

QAction *TicTacToeTaskMenu::preferredEditAction() const
{
    return editStateAction;
}

QList<QAction *> TicTacToeTaskMenu::taskActions() const
{
    QList<QAction *> list;
    list.append(editStateAction);
    return list;
}

TicTacToeTaskMenuFactory::TicTacToeTaskMenuFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{}

QObject *TicTacToeTaskMenuFactory::createExtension(QObject *object,
                                                   const QString &iid,
                                                   QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
        return 0;

    if (TicTacToe *tic = qobject_cast<TicTacToe*>(object))
        return new TicTacToeTaskMenu(tic, parent);

    return 0;
}
