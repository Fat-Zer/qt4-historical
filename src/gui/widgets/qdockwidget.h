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

#ifndef QDOCKWIDGET_H
#define QDOCKWIDGET_H

#include <QtGui/qwidget.h>

class QDockWidgetLayout;
class QDockWidgetPrivate;
class QMainWindow;

class Q_GUI_EXPORT QDockWidget : public QWidget
{
    Q_OBJECT

    Q_FLAGS(DockWidgetFeatures)
    Q_PROPERTY(bool floating READ isFloating WRITE setFloating)
    Q_PROPERTY(DockWidgetFeatures features READ features WRITE setFeatures NOTIFY featuresChanged)
    Q_PROPERTY(Qt::DockWidgetAreas allowedAreas READ allowedAreas
               WRITE setAllowedAreas NOTIFY allowedAreasChanged)

public:
    explicit QDockWidget(const QString &title, QWidget *parent = 0, Qt::WFlags flags = 0);
    explicit QDockWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~QDockWidget();

    QWidget *widget() const;
    void setWidget(QWidget *widget);

    enum DockWidgetFeature {
        DockWidgetClosable    = 0x01,
        DockWidgetMovable     = 0x02,
        DockWidgetFloatable   = 0x04,

        DockWidgetFeatureMask = 0x07,
        AllDockWidgetFeatures = DockWidgetFeatureMask,
        NoDockWidgetFeatures  = 0x00,

        Reserved              = 0xff
    };
    Q_DECLARE_FLAGS(DockWidgetFeatures, DockWidgetFeature)

    void setFeatures(DockWidgetFeatures features);
    DockWidgetFeatures features() const;

    void setFloating(bool floating);
    inline bool isFloating() const { return isWindow(); }

    void setAllowedAreas(Qt::DockWidgetAreas areas);
    Qt::DockWidgetAreas allowedAreas() const;

    inline bool isAreaAllowed(Qt::DockWidgetArea area) const
    { return (allowedAreas() & area) == area; }

    QAction *toggleViewAction() const;

signals:
    void featuresChanged(DockWidgetFeatures features);
    void topLevelChanged(bool topLevel);
    void allowedAreasChanged(Qt::DockWidgetAreas allowedAreas);

protected:
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    bool event(QEvent *event);

private:
    Q_DECLARE_PRIVATE(QDockWidget)
    Q_DISABLE_COPY(QDockWidget)
    Q_PRIVATE_SLOT(d_func(), void toggleView(bool))
    friend class QDockWidgetLayout;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDockWidget::DockWidgetFeatures)

#endif // QDOCKWIDGET_H
