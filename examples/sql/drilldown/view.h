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

#ifndef VIEW_H
#define VIEW_H

#include <QtGui>
#include <QtSql>

class ImageItem;
class InformationWindow;

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(const QString &offices, const QString &images, QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void updateImage(int id, const QString &fileName);

private:
    void addItems();
    InformationWindow* findWindow(int id);
    void showInformation(ImageItem *image);

    QGraphicsScene *scene;
    QList<InformationWindow *> informationWindows;
    QSqlRelationalTableModel *officeTable;
};

#endif
