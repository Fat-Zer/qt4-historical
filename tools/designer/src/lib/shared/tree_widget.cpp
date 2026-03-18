/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "tree_widget_p.h"

#include <QtCore/QPair>
#include <QtCore/QStack>

#include <QtGui/QApplication>
#include <QtGui/QHeaderView>
#include <QtGui/QScrollBar>
#include <QtGui/QItemDelegate>
#include <QtGui/QPainter>
#include <QtGui/QStyle>

class TreeWidgetDelegate: public QItemDelegate
{
public:
    TreeWidgetDelegate(TreeWidget *treeWidget)
        : QItemDelegate(treeWidget) {}


    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const
    {
        QItemDelegate::paint(painter, option, index);

        painter->drawLine(option.rect.x(), option.rect.bottom(),
                            option.rect.right(), option.rect.bottom());

        painter->drawLine(option.rect.right(), option.rect.y(),
                            option.rect.right(), option.rect.bottom());
    }

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        return QItemDelegate::sizeHint(option, index) + QSize(4,4);
    }
};


TreeWidget::TreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    setItemDelegate(new TreeWidgetDelegate(this));

    setAlternatingRowColors(true);
}

TreeWidget::~TreeWidget()
{
}

void TreeWidget::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    QStyleOptionViewItem option = viewOptions();

    if (selectionModel()->isSelected(index))
        painter->fillRect(rect, option.palette.brush(QPalette::Highlight));
    if (model()->hasChildren(index)) {
        static const int size = 9;
        option.state |= QStyle::State_Children;
        option.rect.setRect(rect.width() - (indentation() + size) / 2,
                            rect.y() + (rect.height() - size) / 2, size, size);

        if (isExpanded(index))
            option.state |= QStyle::State_Open;

        painter->fillRect(option.rect, Qt::white);
        style()->drawPrimitive(QStyle::PE_IndicatorBranch, &option, painter, this);
    }
    painter->drawLine(rect.x(), rect.bottom(), rect.right(), rect.bottom());
}
