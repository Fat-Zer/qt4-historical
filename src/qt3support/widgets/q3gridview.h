/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#ifndef Q3GRIDVIEW_H
#define Q3GRIDVIEW_H

#include "Qt3Support/q3scrollview.h"

class Q3GridViewPrivate;

class Q_COMPAT_EXPORT Q3GridView : public Q3ScrollView
{
    Q_OBJECT
    Q_PROPERTY(int numRows READ numRows WRITE setNumRows)
    Q_PROPERTY(int numCols READ numCols WRITE setNumCols)
    Q_PROPERTY(int cellWidth READ cellWidth WRITE setCellWidth)
    Q_PROPERTY(int cellHeight READ cellHeight WRITE setCellHeight)
public:

    Q3GridView(QWidget *parent=0, const char *name=0, Qt::WFlags f=0);
   ~Q3GridView();

    int numRows() const;
    virtual void setNumRows(int);
    int numCols() const;
    virtual void setNumCols(int);

    int cellWidth() const;
    virtual void setCellWidth(int);
    int cellHeight() const;
    virtual void setCellHeight(int);

    QRect cellRect() const;
    QRect cellGeometry(int row, int column);
    QSize gridSize() const;

    int rowAt(int y) const;
    int columnAt(int x) const;

    void repaintCell(int row, int column, bool erase=true);
    void updateCell(int row, int column);
    void ensureCellVisible(int row, int column);

protected:
    virtual void paintCell(QPainter *, int row, int col) = 0;
    virtual void paintEmptyArea(QPainter *p, int cx, int cy, int cw, int ch);

    void drawContents(QPainter *p, int cx, int cy, int cw, int ch);

    virtual void dimensionChange(int, int);

private:
    void drawContents(QPainter*);
    void updateGrid();

    int nrows;
    int ncols;
    int cellw;
    int cellh;
    Q3GridViewPrivate* d;

    Q_DISABLE_COPY(Q3GridView)
};

inline int Q3GridView::cellWidth() const
{ return cellw; }

inline int Q3GridView::cellHeight() const
{ return cellh; }

inline int Q3GridView::rowAt(int y) const
{ return y / cellh; }

inline int Q3GridView::columnAt(int x) const
{ return x / cellw; }

inline int Q3GridView::numRows() const
{ return nrows; }

inline int Q3GridView::numCols() const
{return ncols; }

inline QRect Q3GridView::cellRect() const
{ return QRect(0, 0, cellw, cellh); }

inline QSize Q3GridView::gridSize() const
{ return QSize(ncols * cellw, nrows * cellh); }

#endif // Q3GRIDVIEW_H
