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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef PROMOTETOCUSTOMWIDGETDIALOG_H
#define PROMOTETOCUSTOMWIDGETDIALOG_H

#include <QtGui/QDialog>
#include <QtCore/QPair>

class QDesignerWidgetDataBaseInterface;

namespace Ui {
    class PromoteToCustomWidgetDialog;
} // namespace Ui

class PromoteToCustomWidgetDialog : public QDialog
{
    Q_OBJECT
public:
    PromoteToCustomWidgetDialog(QDesignerWidgetDataBaseInterface *db,
                                const QString &base_class_name,
                                QWidget *parent = 0);
    virtual ~PromoteToCustomWidgetDialog();

    virtual void accept();
    QString includeFile() const;
    QString customClassName() const;

private slots:
    void checkInputs();
    void setIncludeForClass(const QString &name);

private:
    Ui::PromoteToCustomWidgetDialog *ui;
    bool m_automatic_include;
    QDesignerWidgetDataBaseInterface *m_db;
    typedef QPair<QString, QString> PromotedWidgetInfo;
    typedef QList<PromotedWidgetInfo> PromotedWidgetInfoList;
    PromotedWidgetInfoList m_promoted_list;
    QString m_base_class_name;
};

#endif // PROMOTETOCUSTOMWIDGETDIALOG_H
