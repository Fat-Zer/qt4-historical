/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the accessibility module of the Qt Toolkit.
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

#include "qaccessiblewidgets.h"
#include "qaccessiblemenu.h"
#include "simplewidgets.h"
#include "rangecontrols.h"
#include "complexwidgets.h"

#include <qaccessibleplugin.h>
#include <qplugin.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qvariant.h>
#include <qaccessible.h>

class AccessibleFactory : public QAccessiblePlugin
{
public:
    AccessibleFactory();

    QStringList keys() const;
    QAccessibleInterface *create(const QString &classname, QObject *object);
};

AccessibleFactory::AccessibleFactory()
{
}

QStringList AccessibleFactory::keys() const
{
    QStringList list;
    list << "QLineEdit";
    list << "QComboBox";
    list << "QSpinBox";
    list << "QScrollBar";
    list << "QSlider";
    list << "QToolButton";
    list << "QCheckBox";
    list << "QRadioButton";
    list << "QPushButton";
    list << "QButton";
    list << "QAbstractScrollAreaWidget";
    list << "QClipperWidget";
    list << "QDialog";
    list << "QMessageBox";
    list << "QMainWindow";
    list << "QLabel";
    list << "QLCDNumber";
    list << "QGroupBox";
    list << "QStatusBar";
    list << "QProgressBar";
    list << "QMenuBar";
    list << "Q3PopupMenu";
    list << "QMenu";
    list << "QHeaderView";
    list << "QTabBar";
    list << "QToolBar";
    list << "QWorkspaceChild";
    list << "QSizeGrip";
    list << "QSplitter";
    list << "QSplitterHandle";
    list << "QTipLabel";
    list << "QFrame";
    list << "QWidgetStack";

    return list;
}

QAccessibleInterface *AccessibleFactory::create(const QString &classname, QObject *object)
{
    QAccessibleInterface *iface = 0;
    if (!object || !object->isWidgetType())
        return iface;
    QWidget *widget = static_cast<QWidget*>(object);

    if (classname == "QLineEdit") {
        iface = new QAccessibleLineEdit(widget);
    } else if (classname == "QComboBox") {
        iface = new QAccessibleComboBox(widget);
    } else if (classname == "QSpinBox") {
        iface = new QAccessibleSpinBox(widget);
    } else if (classname == "QScrollBar") {
        iface = new QAccessibleScrollBar(widget);
    } else if (classname == "QSlider") {
        iface = new QAccessibleSlider(widget);
    } else if (classname == "QToolButton") {
        Role role = NoRole;
        QToolButton *tb = qobject_cast<QToolButton*>(widget);
        if (!tb->menu())
            role = tb->isCheckable() ? CheckBox : PushButton;
        else if (!tb->popupMode() != QToolButton::DelayedPopup)
            role = ButtonDropDown;
        else
            role = ButtonMenu;
        iface = new QAccessibleToolButton(widget, role);
    } else if (classname == "QCheckBox") {
        iface = new QAccessibleButton(widget, CheckBox);
    } else if (classname == "QRadioButton") {
        iface = new QAccessibleButton(widget, RadioButton);
    } else if (classname == "QPushButton") {
        Role role = NoRole;
        QPushButton *pb = qobject_cast<QPushButton*>(widget);
        if (pb->menu())
            role = ButtonMenu;
        else if (pb->isCheckable())
            role = CheckBox;
        else
            role = PushButton;
        iface = new QAccessibleButton(widget, role);
    } else if (classname == "QButton") {
        iface = new QAccessibleButton(widget, PushButton);
    } else if (classname == "QAbstractScrollAreaWidget") {
        iface = new QAccessibleViewport(widget, widget->parentWidget());
    } else if (classname == "QClipperWidget") {
        iface = new QAccessibleViewport(widget, widget->parentWidget()->parentWidget());
    } else if (classname == "QDialog") {
        iface = new QAccessibleWidget(widget, Dialog);
    } else if (classname == "QMessageBox") {
        iface = new QAccessibleWidget(widget, AlertMessage);
    } else if (classname == "QMainWindow") {
        iface = new QAccessibleWidget(widget, Application);
    } else if (classname == "QLabel" || classname == "QLCDNumber") {
        iface = new QAccessibleDisplay(widget);
    } else if (classname == "QGroupBox") {
        iface = new QAccessibleDisplay(widget, Grouping);
    } else if (classname == "QStatusBar") {
        iface = new QAccessibleWidget(widget, StatusBar);
    } else if (classname == "QProgressBar") {
        iface = new QAccessibleDisplay(widget);
    } else if (classname == "QToolBar") {
        iface = new QAccessibleWidget(widget, ToolBar, widget->windowTitle());
    } else if (classname == "QMenuBar") {
        iface = new QAccessibleMenuBar(widget);
    } else if (classname == "QMenu") {
        iface = new QAccessibleMenu(widget);
    } else if (classname == "Q3PopupMenu") {
        iface = new QAccessibleMenu(widget);
    } else if (classname == "QHeaderView") {
        iface = new QAccessibleHeader(widget);
    } else if (classname == "QTabBar") {
        iface = new QAccessibleTabBar(widget);
    } else if (classname == "QWorkspaceChild") {
        iface = new QAccessibleWidget(widget, Window);
    } else if (classname == "QSizeGrip") {
        iface = new QAccessibleWidget(widget, Grip);
    } else if (classname == "QSplitter") {
        iface = new QAccessibleWidget(widget, Splitter);
    } else if (classname == "QSplitterHandle") {
        iface = new QAccessibleWidget(widget, Grip);
    } else if (classname == "QTipLabel") {
        iface = new QAccessibleWidget(widget, ToolTip);
    } else if (classname == "QFrame") {
        iface = new QAccessibleWidget(widget, Border);
    }

    return iface;
}

Q_EXPORT_PLUGIN(AccessibleFactory)
