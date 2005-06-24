/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "tabordereditor_tool.h"
#include "tabordereditor.h"

#include <QtDesigner/QtDesigner>

#include <QtCore/QEvent>
#include <QtGui/QAction>

using namespace qdesigner_internal;

TabOrderEditorTool::TabOrderEditorTool(QDesignerFormWindowInterface *formWindow, QObject *parent)
    : QDesignerFormWindowToolInterface(parent),
      m_formWindow(formWindow)
{
    m_action = new QAction(tr("Edit Tab Order"), this);
}

TabOrderEditorTool::~TabOrderEditorTool()
{
}

QDesignerFormEditorInterface *TabOrderEditorTool::core() const
{
    return m_formWindow->core();
}

QDesignerFormWindowInterface *TabOrderEditorTool::formWindow() const
{
    return m_formWindow;
}

bool TabOrderEditorTool::handleEvent(QWidget *widget, QWidget *managedWidget, QEvent *event)
{
    Q_UNUSED(widget);
    Q_UNUSED(managedWidget);

    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        return true;

    return false;
}

QWidget *TabOrderEditorTool::editor() const
{
    if (!m_editor) {
        Q_ASSERT(formWindow() != 0);
        m_editor = new TabOrderEditor(formWindow(), 0);
        connect(formWindow(), SIGNAL(mainContainerChanged(QWidget*)), m_editor, SLOT(setBackground(QWidget*)));
    }

    return m_editor;
}

void TabOrderEditorTool::activated()
{
    connect(formWindow(), SIGNAL(changed()),
                m_editor, SLOT(updateBackground()));
    m_editor->updateBackground();
}

void TabOrderEditorTool::deactivated()
{
    disconnect(formWindow(), SIGNAL(changed()),
                m_editor, SLOT(updateBackground()));
}

QAction *TabOrderEditorTool::action() const
{
    return m_action;
}

