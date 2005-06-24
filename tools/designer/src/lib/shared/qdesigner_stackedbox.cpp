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

#include "qdesigner_stackedbox_p.h"
#include "abstractformwindow.h"
#include "qdesigner_command_p.h"
#include "qtundo_p.h"

#include <QtDesigner/QtDesigner>
#include <QtDesigner/QExtensionManager>

#include <QtGui/QToolButton>
#include <QtGui/QAction>
#include <QtGui/qevent.h>
#include <QtCore/qdebug.h>

QDesignerStackedWidget::QDesignerStackedWidget(QWidget *parent)
    : QStackedWidget(parent), m_actionDeletePage(0)
{
    prev = new QToolButton();
    prev->setAttribute(Qt::WA_NoChildEventsForParent, true);
    prev->setParent(this);

    prev->setObjectName(QLatin1String("__qt__passive_prev"));
    prev->setArrowType(Qt::LeftArrow);
    prev->setAutoRaise(true);
    prev->setAutoRepeat(true);
    prev->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
    connect(prev, SIGNAL(clicked()), this, SLOT(prevPage()));

    next = new QToolButton();
    next->setAttribute(Qt::WA_NoChildEventsForParent, true);
    next->setParent(this);
    next->setObjectName(QLatin1String("__qt__passive_next"));
    next->setArrowType(Qt::RightArrow);
    next->setAutoRaise(true);
    next->setAutoRepeat(true);
    next->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
    connect(next, SIGNAL(clicked()), this, SLOT(nextPage()));

    updateButtons();

    m_actionPreviousPage = new QAction(tr("Previous Page"), this);
    connect(m_actionPreviousPage, SIGNAL(triggered()), this, SLOT(prevPage()));

    m_actionNextPage = new QAction(tr("Next Page"), this);
    connect(m_actionNextPage, SIGNAL(triggered()), this, SLOT(nextPage()));

    m_actionDeletePage = new QAction(tr("Delete Page"), this);
    connect(m_actionDeletePage, SIGNAL(triggered()), this, SLOT(removeCurrentPage()));

    m_actionInsertPage = new QAction(tr("Add Page"), this);
    connect(m_actionInsertPage, SIGNAL(triggered()), this, SLOT(addPage()));
}

void QDesignerStackedWidget::removeCurrentPage()
{
    if (currentIndex() == -1)
        return;

    if (QDesignerFormWindowInterface *fw = QDesignerFormWindowInterface::findFormWindow(this)) {
        DeleteStackedWidgetPageCommand *cmd = new DeleteStackedWidgetPageCommand(fw);
        cmd->init(this);
        fw->commandHistory()->push(cmd);
    }
}

void QDesignerStackedWidget::addPage()
{
    if (QDesignerFormWindowInterface *fw = QDesignerFormWindowInterface::findFormWindow(this)) {
        AddStackedWidgetPageCommand *cmd = new AddStackedWidgetPageCommand(fw);
        cmd->init(this);
        fw->commandHistory()->push(cmd);
    }
}

void QDesignerStackedWidget::updateButtons()
{
    if (prev) {
        prev->setGeometry(width() - 31, 1, 15, 15);
        prev->show();
        prev->raise();
    }

    if (next) {
        next->setGeometry(width() - 16, 1, 15, 15);
        next->show();
        next->raise();
    }
}

void QDesignerStackedWidget::prevPage()
{
    if (count() == 0) {
        // nothing to do
        return;
    }

    if (QDesignerFormWindowInterface *fw = QDesignerFormWindowInterface::findFormWindow(this)) {
        int newIndex = currentIndex() - 1;
        if (newIndex < 0)
            newIndex = count() - 1;

        SetPropertyCommand *cmd = new SetPropertyCommand(fw);
        cmd->init(this, QLatin1String("currentIndex"), newIndex);
        fw->commandHistory()->push(cmd);
        updateButtons();
        fw->emitSelectionChanged();
    } else {
        setCurrentIndex(qMax(0, currentIndex() - 1));
        updateButtons();
    }
}

void QDesignerStackedWidget::nextPage()
{
    if (count() == 0) {
        // nothing to do
        return;
    }

    if (QDesignerFormWindowInterface *fw = QDesignerFormWindowInterface::findFormWindow(this)) {
        SetPropertyCommand *cmd = new SetPropertyCommand(fw);
        cmd->init(this, QLatin1String("currentIndex"), (currentIndex() + 1) % count());
        fw->commandHistory()->push(cmd);
        updateButtons();
        fw->emitSelectionChanged();
    } else {
        setCurrentIndex((currentIndex() + 1) % count());
        updateButtons();
    }
}

bool QDesignerStackedWidget::event(QEvent *e)
{
    if (e->type() == QEvent::LayoutRequest) {
        if (m_actionDeletePage)
            m_actionDeletePage->setEnabled(count() > 1);
        updateButtons();
    }

    return QStackedWidget::event(e);
}

void QDesignerStackedWidget::childEvent(QChildEvent *e)
{
    QStackedWidget::childEvent(e);
    updateButtons();
}

void QDesignerStackedWidget::resizeEvent(QResizeEvent *e)
{
    QStackedWidget::resizeEvent(e);
    updateButtons();
}

void QDesignerStackedWidget::showEvent(QShowEvent *e)
{
    QStackedWidget::showEvent(e);
    updateButtons();
}

QString QDesignerStackedWidget::currentPageName() const
{
    if (currentIndex() == -1)
        return QString();

    return widget(currentIndex())->objectName();
}

void QDesignerStackedWidget::setCurrentPageName(const QString &pageName)
{
    if (currentIndex() == -1)
        return;

    if (QWidget *w = widget(currentIndex())) {
        w->setObjectName(pageName);
    }
}
