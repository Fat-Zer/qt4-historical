/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QTABBAR_H
#define QTABBAR_H

#include "QtGui/qwidget.h"

class QIcon;
class QTabBarPrivate;

class Q_GUI_EXPORT QTabBar: public QWidget
{
    Q_OBJECT

    Q_ENUMS(Shape)
    Q_PROPERTY(Shape shape READ shape WRITE setShape)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(bool drawBase READ drawBase WRITE setDrawBase)

public:
    explicit QTabBar(QWidget* parent=0);
    ~QTabBar();

    enum Shape { RoundedNorth, RoundedSouth, RoundedWest, RoundedEast,
                 TriangularNorth, TriangularSouth, TriangularWest, TriangularEast
#if defined(QT3_SUPPORT) && !defined(Q_MOC_RUN)
                , RoundedAbove = RoundedNorth, RoundedBelow = RoundedSouth,
                TriangularAbove = TriangularNorth, TriangularBelow = TriangularSouth
#endif
    };

    Shape shape() const;
    void setShape(Shape shape);

    int addTab(const QString &text);
    int addTab(const QIcon &icon, const QString &text);

    int insertTab(int index, const QString &text);
    int insertTab(int index, const QIcon&icon, const QString &text);

    void removeTab(int index);

    bool isTabEnabled(int index) const;
    void setTabEnabled(int index, bool);

    QString tabText(int index) const;
    void setTabText(int index, const QString &text);

    QIcon tabIcon(int index) const;
    void setTabIcon(int index, const QIcon &icon);

    void setTabToolTip(int index, const QString &tip);
    QString tabToolTip(int index) const;

    void setTabData(int index, const QVariant &data);
    QVariant tabData(int index) const;

    QRect tabRect(int index) const;

    int currentIndex() const;
    int count() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setDrawBase(bool drawTheBase);
    bool drawBase() const;

public slots:
    void setCurrentIndex(int index);

signals:
    void currentChanged(int index);

protected:
    virtual QSize tabSizeHint(int index) const;
    virtual void tabInserted(int index);
    virtual void tabRemoved(int index);
    virtual void tabLayoutChange();

    bool event(QEvent *);
    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent (QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);
    void mouseReleaseEvent (QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void changeEvent(QEvent *);

#ifdef QT3_SUPPORT
public slots:
    QT_MOC_COMPAT void setCurrentTab(int index) { setCurrentIndex(index); }
signals:
    QT_MOC_COMPAT void selected(int);
#endif

private:
    Q_DISABLE_COPY(QTabBar)
    Q_DECLARE_PRIVATE(QTabBar)
    Q_PRIVATE_SLOT(d_func(), void scrollTabs())
};

#endif // QTABBAR_H
