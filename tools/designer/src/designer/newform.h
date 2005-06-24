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

#ifndef NEWFORM_H
#define NEWFORM_H

#include "ui_newform.h"

#include <QDialog>

class QDesignerWorkbench;

class NewForm: public QDialog
{
    Q_OBJECT
public:
    NewForm(QDesignerWorkbench *workbench, QWidget *parentWidget);
    virtual ~NewForm();

    QDesignerWorkbench *workbench() const;

private slots:
    void on_createButton_clicked();
    void on_closeButton_clicked();
    void on_openButton_clicked();
    void on_treeWidget_itemActivated(QTreeWidgetItem *item);
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *);
    void on_treeWidget_itemPressed(QTreeWidgetItem *item);

private:
    QIcon formPreviewIcon(const QString &fileName);
    void loadFrom(const QString &path, bool resourceFile);

private:
    QDesignerWorkbench *m_workbench;
    Ui::NewForm ui;
};

#endif // NEWFORM_H
