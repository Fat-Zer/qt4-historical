/****************************************************************************
**
** Copyright (C) 2006-2006 Trolltech ASA. All rights reserved.
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

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <q3popupmenu.h>
#include <q3mainwindow.h>
#include <q3intdict.h>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

class BouncyLogo : public QGraphicsPixmapItem {
    void initSpeed();
public:
    BouncyLogo();
    void advance(int);
    int type() const;

    QPainterPath shape() const;

    void initPos();
private:
    qreal xvel;
    qreal yvel;
};


class FigureEditor : public QGraphicsView {
    Q_OBJECT

public:
    FigureEditor(QGraphicsScene&, QWidget* parent=0, const char* name=0, Qt::WindowFlags f=0);
    void clear();

signals:
    void status(const QString&);
};

class Main : public Q3MainWindow {
    Q_OBJECT

public:
    Main(QGraphicsScene&, QWidget* parent=0, const char* name=0, Qt::WindowFlags f=0);
    ~Main();

public slots:
    void help();

private slots:
    void aboutQt();
    void newView();
    void clear();
    void init();

    void addSprite();
    void addCircle();
    void addHexagon();
    void addPolygon();
    void addSpline();
    void addText();
    void addLine();
    void addRectangle();
    void addMesh();
    void addLogo();
    void addButterfly();

    void enlarge();
    void shrink();
    void rotateClockwise();
    void rotateCounterClockwise();
    void zoomIn();
    void zoomOut();
    void mirror();
    void moveL();
    void moveR();
    void moveU();
    void moveD();

    void print();

private:
    QGraphicsScene& canvas;
    FigureEditor *editor;

    Q3PopupMenu* options;
    QPrinter* printer;
    int dbf_id;
};

#endif
