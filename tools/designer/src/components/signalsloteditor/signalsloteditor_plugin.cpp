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

#include "signalsloteditor_plugin.h"
#include "signalsloteditor_tool.h"

#include <QtDesigner/QtDesigner>

SignalSlotEditorPlugin::SignalSlotEditorPlugin()
    : m_initialized(false), m_action(0)
{
}

SignalSlotEditorPlugin::~SignalSlotEditorPlugin()
{
}

bool SignalSlotEditorPlugin::isInitialized() const
{
    return m_initialized;
}

void SignalSlotEditorPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_ASSERT(!isInitialized());

    m_action = new QAction(tr("Edit Signals/Slots"), this);
    m_action->setShortcut(tr("F4"));
    QIcon icon(QIcon(core->resourceLocation() + QLatin1String("/signalslottool.png")));
    m_action->setIcon(icon);
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

QDesignerFormEditorInterface *SignalSlotEditorPlugin::core() const
{
    return m_core;
}

void SignalSlotEditorPlugin::addFormWindow(QDesignerFormWindowInterface *formWindow)
{
    Q_ASSERT(formWindow != 0);
    Q_ASSERT(m_tools.contains(formWindow) == false);

    SignalSlotEditorTool *tool = new SignalSlotEditorTool(formWindow, this);
    connect(m_action, SIGNAL(triggered()), tool->action(), SLOT(trigger()));
    m_tools[formWindow] = tool;
    formWindow->registerTool(tool);
}

void SignalSlotEditorPlugin::removeFormWindow(QDesignerFormWindowInterface *formWindow)
{
    Q_ASSERT(formWindow != 0);
    Q_ASSERT(m_tools.contains(formWindow) == true);

    SignalSlotEditorTool *tool = m_tools.value(formWindow);
    m_tools.remove(formWindow);
    disconnect(m_action, SIGNAL(triggered()), tool->action(), SLOT(trigger()));
    // ### FIXME disable the tool

    delete tool;
}

QAction *SignalSlotEditorPlugin::action() const
{
    return m_action;
}

void SignalSlotEditorPlugin::activeFormWindowChanged(QDesignerFormWindowInterface *formWindow)
{
    m_action->setEnabled(formWindow != 0);
}
