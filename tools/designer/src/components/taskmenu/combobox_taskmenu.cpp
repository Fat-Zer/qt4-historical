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

#include "combobox_taskmenu.h"
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

ComboBoxTaskMenu::ComboBoxTaskMenu(QComboBox *button, QObject *parent)
    : QDesignerTaskMenu(button, parent),
      m_comboBox(button)
{
    m_editItemsAction = new QAction(this);
    m_editItemsAction->setText(tr("Edit Items..."));
    connect(m_editItemsAction, SIGNAL(triggered()), this, SLOT(editItems()));
    m_taskActions.append(m_editItemsAction);

    QAction *sep = new QAction(this);
    sep->setSeparator(true);
    m_taskActions.append(sep);
}

ComboBoxTaskMenu::~ComboBoxTaskMenu()
{
}

QAction *ComboBoxTaskMenu::preferredEditAction() const
{
    return m_editItemsAction;
}

QList<QAction*> ComboBoxTaskMenu::taskActions() const
{
    return m_taskActions + QDesignerTaskMenu::taskActions();
}

void ComboBoxTaskMenu::editItems()
{
    m_formWindow = QDesignerFormWindowInterface::findFormWindow(m_comboBox);
    if (m_formWindow.isNull())
        return;

    Q_ASSERT(m_comboBox != 0);

    ListWidgetEditor dlg(m_formWindow, m_comboBox->window());
    dlg.fillContentsFromComboBox(m_comboBox);
    if (dlg.exec() == QDialog::Accepted) {
        m_comboBox->clear();
        for (int i=0; i<dlg.count(); ++i) {
            m_comboBox->addItem(dlg.icon(i), dlg.text(i));
        }
    }
}

ComboBoxTaskMenuFactory::ComboBoxTaskMenuFactory(QExtensionManager *extensionManager)
    : QExtensionFactory(extensionManager)
{
}

QObject *ComboBoxTaskMenuFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (QComboBox *button = qobject_cast<QComboBox*>(object)) {
        if (iid == Q_TYPEID(QDesignerTaskMenuExtension)) {
            return new ComboBoxTaskMenu(button, parent);
        }
    }

    return 0;
}

void ComboBoxTaskMenu::updateSelection()
{
    if (m_editor)
        m_editor->deleteLater();
}

