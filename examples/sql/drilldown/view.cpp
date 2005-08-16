/****************************************************************************
**
** Copyright (C) 2006-2007 Trolltech ASA. All rights reserved.
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

#include "informationwindow.h"
#include "imageitem.h"
#include "view.h"

View::View(const QString &offices, const QString &images, QWidget *parent)
    : QGraphicsView(parent)
{
    officeTable = new QSqlRelationalTableModel(this);
    officeTable->setTable(offices);
    officeTable->setRelation(1, QSqlRelation(images, "locationid", "file"));
    officeTable->select();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 465, 615);
    setScene(scene);

    addItems();

    QGraphicsPixmapItem *logo = scene->addPixmap(QPixmap(":/logo.png"));
    logo->setPos(30, 515);

    setMinimumSize(470, 620);
    setMaximumSize(470, 620);
    setWindowTitle(tr("Trolltech World Wide"));
}

void View::addItems()
{
    int officeCount = officeTable->rowCount();

    int imageOffset = 150;
    int leftMargin = 70;
    int topMargin = 40;

    for (int i = 0; i < officeCount; i++) {
        ImageItem *image;
        QGraphicsTextItem *label;
        QSqlRecord record = officeTable->record(i);

        int id = record.value("id").toInt();
        QString file = record.value("file").toString();
        QString location = record.value("location").toString();

        int columnOffset = ((i / 3) * 37);
        int x = ((i / 3) * imageOffset) + leftMargin + columnOffset;
        int y = ((i % 3) * imageOffset) + topMargin;

        image = new ImageItem(id, QPixmap(":/" + file));
        image->setData(0, i);
        image->setPos(x, y);
        scene->addItem(image);

        label = scene->addText(location);
        QPointF labelOffset((150 - label->boundingRect().width()) / 2, 120.0);
        label->setPos(QPointF(x, y) + labelOffset);
    }
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if (QGraphicsItem *item = itemAt(event->pos())) {
        if (ImageItem *image = qgraphicsitem_cast<ImageItem *>(item))
            showInformation(image);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void View::showInformation(ImageItem *image)
{
    int id = image->id();
    if (id < 0 || id >= officeTable->rowCount())
        return;

    InformationWindow *window = findWindow(id);
    if (window && window->isVisible()) {
        window->raise();
        window->activateWindow();
    } else if (window && !window->isVisible()) {
        window->show();
    } else {
        InformationWindow *window;
        window = new InformationWindow(id, officeTable, this);

        connect(window, SIGNAL(imageChanged(int, QString)),
                this, SLOT(updateImage(int, QString)));

        window->move(pos() + QPoint(20, 40));
        window->show();
        informationWindows.append(window);
    }
}

void View::updateImage(int id, const QString &fileName)
{
    QList<QGraphicsItem *> items = scene->items();

    while(!items.empty()) {
        QGraphicsItem *item = items.takeFirst();

        if (ImageItem *image = qgraphicsitem_cast<ImageItem *>(item)) {
            if (image->id() == id){
                image->setPixmap(QPixmap(":/" +fileName));
                image->adjust();
                break;
            }
        }
    }
}

InformationWindow* View::findWindow(int id)
{
    QList<InformationWindow*>::iterator i, beginning, end;

    beginning = informationWindows.begin();
    end = informationWindows.end();

    for (i = beginning; i != end; ++i) {
        InformationWindow *window = (*i);
        if (window && (window->id() == id))
            return window;
    }
    return 0;
}

