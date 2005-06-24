/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#ifndef QDESIGNER_H
#define QDESIGNER_H

#include <QtCore/QPointer>
#include <QtGui/QApplication>

#include "qdesigner_toolwindow.h"

#define qDesigner \
    (static_cast<QDesigner*>(QCoreApplication::instance()))

class QDesignerSettings;
class QDesignerWorkbench;
class QDesignerServer;
class QDesignerClient;

class QDesigner: public QApplication
{
    Q_OBJECT
public:
    QDesigner(int &argc, char **argv);
    virtual ~QDesigner();

    QDesignerWorkbench *workbench() const;
    QDesignerServer *server() const;
    QDesignerToolWindow *mainWindow() const;
    void setMainWindow(QDesignerToolWindow *tw);

protected:
    bool event(QEvent *ev);

signals:
    void initialized();

private slots:
    void initialize();

private:
    QDesignerServer *m_server;
    QDesignerClient *m_client;
    QDesignerWorkbench *m_workbench;
    QPointer<QDesignerToolWindow> m_mainWindow;
};

#endif // QDESIGNER_H
