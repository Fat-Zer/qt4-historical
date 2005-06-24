/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#ifndef QDESIGNER_TOOLWINDOW_H
#define QDESIGNER_TOOLWINDOW_H

#include <QtCore/QPointer>
#include <QtGui/QMainWindow>

class QDesignerWorkbench;

class QDesignerToolWindow: public QMainWindow
{
    Q_OBJECT
public:
    QDesignerToolWindow(QDesignerWorkbench *workbench, QWidget *parent = 0, Qt::WindowFlags flags = Qt::Window);
    virtual ~QDesignerToolWindow();

    QDesignerWorkbench *workbench() const;
    QAction *action() const;

    void setSaveSettingsOnClose(bool save);
    bool saveSettingsOnClose() const;

    virtual Qt::DockWidgetArea dockWidgetAreaHint() const;
    virtual QRect geometryHint() const;

private slots:
    void showMe(bool);

protected:
    virtual void showEvent(QShowEvent *e);
    virtual void hideEvent(QHideEvent *e);
    virtual void changeEvent(QEvent *e);
    virtual void closeEvent(QCloseEvent *e);

private:
    QDesignerWorkbench *m_workbench;
    QAction *m_action;
    bool m_saveSettings;
};

#endif // QDESIGNER_TOOLWINDOW_H
