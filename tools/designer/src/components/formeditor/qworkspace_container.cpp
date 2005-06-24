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

#include "qworkspace_container.h"

#include <QtCore/qdebug.h>

#include <QtGui/QWorkspace>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QStatusBar>

using namespace qdesigner_internal;

QWorkspaceContainer::QWorkspaceContainer(QWorkspace *widget, QObject *parent)
    : QObject(parent),
      m_workspace(widget)
{
    Q_ASSERT(m_workspace->windowList(QWorkspace::CreationOrder).isEmpty());
}

int QWorkspaceContainer::count() const
{
    return m_workspace->windowList(QWorkspace::CreationOrder).count();
}

QWidget *QWorkspaceContainer::widget(int index) const
{
    return m_workspace->windowList(QWorkspace::CreationOrder).at(index);
}

int QWorkspaceContainer::currentIndex() const
{
    return m_workspace->windowList(QWorkspace::CreationOrder).indexOf(m_workspace->activeWindow());
}

void QWorkspaceContainer::setCurrentIndex(int index)
{
    m_workspace->setActiveWindow(m_workspace->windowList(QWorkspace::CreationOrder).at(index));
}

void QWorkspaceContainer::addWidget(QWidget *widget)
{
    QWidget *frame = m_workspace->addWindow(widget, Qt::Window);
    frame->show();
}

void QWorkspaceContainer::insertWidget(int index, QWidget *widget)
{
    Q_UNUSED(index);

    addWidget(widget);
}

void QWorkspaceContainer::remove(int index)
{
    Q_UNUSED(index);
}

QWorkspaceContainerFactory::QWorkspaceContainerFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{
}

QObject *QWorkspaceContainerFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerContainerExtension))
        return 0;

    if (QWorkspace *w = qobject_cast<QWorkspace*>(object))
        return new QWorkspaceContainer(w, parent);

    return 0;
}

