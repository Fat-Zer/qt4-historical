/****************************************************************************
**
** Copyright (C) 2005-2006 Trolltech AS. All rights reserved.
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

#include <QtGui>

#include "multipagewidget.h"

MultiPageWidget::MultiPageWidget(QWidget *parent)
    : QWidget(parent)
{
    comboBox = new QComboBox();
    comboBox->setObjectName("__qt__passive_comboBox");
    stackWidget = new QStackedWidget();

    connect(comboBox, SIGNAL(activated(int)),
            stackWidget, SLOT(setCurrentIndex(int)));

    layout = new QVBoxLayout();
    layout->addWidget(comboBox);
    layout->addWidget(stackWidget);
    setLayout(layout);
}

QSize MultiPageWidget::sizeHint() const
{
    return QSize(200, 150);
}

void MultiPageWidget::addPage(QWidget *page)
{
    page->setParent(stackWidget);
    page->setObjectName("widget");

    stackWidget->addWidget(page);
    comboBox->addItem(tr("Page %1").arg(comboBox->count() + 1));

    stackWidget->setCurrentIndex(comboBox->count() -1 );
    comboBox->setCurrentIndex(comboBox->count() -1 );
}

void MultiPageWidget::removePage(int index)
{
    QWidget *widget = stackWidget->widget(index);
    stackWidget->removeWidget(widget);

    comboBox->removeItem(index);
}

int MultiPageWidget::count()
{
    return stackWidget->count();
}

int MultiPageWidget::currentIndex()
{
    return stackWidget->currentIndex();
}

void MultiPageWidget::insertPage(int index, QWidget *page)
{
    page->setParent(stackWidget);
    page->setObjectName("widget");

    stackWidget->insertWidget(index, page);
    comboBox->insertItem(index, tr("Page %1").arg(comboBox->count() + 1));

    stackWidget->setCurrentIndex(index );
    comboBox->setCurrentIndex(index );
}

void MultiPageWidget::setCurrentIndex(int index)
{
    stackWidget->setCurrentIndex(index);
    comboBox->setCurrentIndex(index);
}

QWidget* MultiPageWidget::widget(int index)
{
    return stackWidget->widget(index);
}

QString MultiPageWidget::pageTitle() const
{
    return comboBox->currentText();
}

void MultiPageWidget::setPageTitle(QString const &newTitle)
{
    comboBox->setItemText(currentIndex(), newTitle);
}
