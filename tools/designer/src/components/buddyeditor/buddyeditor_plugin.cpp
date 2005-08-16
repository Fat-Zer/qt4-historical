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

#include <QtGui/QAction>

#include "buddyeditor_plugin.h"
#include "buddyeditor_tool.h"

#include <QtDesigner/QtDesigner>

using namespace qdesigner_internal;

BuddyEditorPlugin::BuddyEditorPlugin()
    : m_initialized(false)
{
}

BuddyEditorPlugin::~BuddyEditorPlugin()
{
}

bool BuddyEditorPlugin::isInitialized() const
{
    return m_initialized;
}

void BuddyEditorPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_ASSERT(!isInitialized());

    m_action = new QAction(tr("Edit Buddies"), this);
    m_action->setIcon(QIcon(core->resourceLocation() + QLatin1String("/buddytool.png")));
    m_action->setIcon(QIcon(core->resourceLocation() + QLatin1String("/buddytool.png")));
    m_action->setEnabled(false);

    setParent(core);
    m_core = core;
    m_initialized = true;

    connect(core->formWindowManager(), SIGNAL(formWindowAdded(QDesignerFormWindowInterface*)),
            this, SLOT(addFormWindow(QDesignerFormWindowInterface*)));

    connect(core->formWindowManager(), SIGNAL(formWindowRemoved(QDesignerFormWindowInterface*)),
            this, SLOT(removeFormWindow(QDesignerFormWindowInterface*)));

    connect(core->formWindowManager(), SIGNAL(activeFormWindowChanged(QDesignerFormWindowInterface*)),
                this, SLOT(activeFormWindowChanged(QDesignerFormWindowInterface*)));
}

QDesignerFormEditorInterface *BuddyEditorPlugin::core() const
{
    return m_core;
}

void BuddyEditorPlugin::addFormWindow(QDesignerFormWindowInterface *formWindow)
{
    Q_ASSERT(formWindow != 0);
    Q_ASSERT(m_tools.contains(formWindow) == false);

    BuddyEditorTool *tool = new BuddyEditorTool(formWindow, this);
    m_tools[formWindow] = tool;
    connect(m_action, SIGNAL(triggered()), tool->action(), SLOT(trigger()));
    formWindow->registerTool(tool);
}

void BuddyEditorPlugin::removeFormWindow(QDesignerFormWindowInterface *formWindow)
{
    Q_ASSERT(formWindow != 0);
    Q_ASSERT(m_tools.contains(formWindow) == true);

    BuddyEditorTool *tool = m_tools.value(formWindow);
    m_tools.remove(formWindow);
    disconnect(m_action, SIGNAL(triggered()), tool->action(), SLOT(trigger()));
    // ### FIXME disable the tool

    delete tool;
}

QAction *BuddyEditorPlugin::action() const
{
    return m_action;
}

void BuddyEditorPlugin::activeFormWindowChanged(QDesignerFormWindowInterface *formWindow)
{
    m_action->setEnabled(formWindow != 0);
}
