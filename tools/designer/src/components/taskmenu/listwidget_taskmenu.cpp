/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#include "listwidget_taskmenu.h"
#include "inplace_editor.h"
#include "listwidgeteditor.h"

#include <QtDesigner/QtDesigner>

#include <QtGui/QAction>
#include <QtGui/QStyle>
#include <QtGui/QStyleOption>

#include <QtCore/QEvent>
#include <QtCore/QVariant>
#include <QtCore/qdebug.h>

using namespace qdesigner_internal;

ListWidgetTaskMenu::ListWidgetTaskMenu(QListWidget *button, QObject *parent)
    : QDesignerTaskMenu(button, parent),
      m_listWidget(button)
{
    m_editItemsAction = new QAction(this);
    m_editItemsAction->setText(tr("Edit Items..."));
    connect(m_editItemsAction, SIGNAL(triggered()), this, SLOT(editItems()));
    m_taskActions.append(m_editItemsAction);

    QAction *sep = new QAction(this);
    sep->setSeparator(true);
    m_taskActions.append(sep);
}

ListWidgetTaskMenu::~ListWidgetTaskMenu()
{
}

QAction *ListWidgetTaskMenu::preferredEditAction() const
{
    return m_editItemsAction;
}

QList<QAction*> ListWidgetTaskMenu::taskActions() const
{
    return m_taskActions + QDesignerTaskMenu::taskActions();
}

void ListWidgetTaskMenu::editItems()
{
    m_formWindow = QDesignerFormWindowInterface::findFormWindow(m_listWidget);
    if (m_formWindow.isNull())
        return;

    Q_ASSERT(m_listWidget != 0);

    ListWidgetEditor dlg(m_formWindow, m_listWidget->window());
    dlg.fillContentsFromListWidget(m_listWidget);
    if (dlg.exec() == QDialog::Accepted) {
        m_listWidget->clear();
        for (int i=0; i<dlg.count(); ++i) {
            QListWidgetItem *item = new QListWidgetItem(dlg.text(i));
            item->setIcon(dlg.icon(i));
            m_listWidget->addItem(item);
        }
    }
}

ListWidgetTaskMenuFactory::ListWidgetTaskMenuFactory(QExtensionManager *extensionManager)
    : QExtensionFactory(extensionManager)
{
}

QObject *ListWidgetTaskMenuFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (QListWidget *button = qobject_cast<QListWidget*>(object)) {
        if (iid == Q_TYPEID(QDesignerTaskMenuExtension)) {
            return new ListWidgetTaskMenu(button, parent);
        }
    }

    return 0;
}

void ListWidgetTaskMenu::updateSelection()
{
    if (m_editor)
        m_editor->deleteLater();
}

