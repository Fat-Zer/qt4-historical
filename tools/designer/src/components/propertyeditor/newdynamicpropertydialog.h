/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

#ifndef NEWDYNAMICPROPERTYDIALOG_P_H
#define NEWDYNAMICPROPERTYDIALOG_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "propertyeditor_global.h"
#include <QtGui/QDialog>
#include <QVariant>

class QAbstractButton;

namespace qdesigner_internal {

namespace Ui
{
    class NewDynamicPropertyDialog;
}

class QT_PROPERTYEDITOR_EXPORT NewDynamicPropertyDialog: public QDialog
{
    Q_OBJECT
public:
    NewDynamicPropertyDialog(QWidget *parent = 0);
    ~NewDynamicPropertyDialog();

    void setReservedNames(const QStringList &names);

    QString propertyName() const;
    QVariant propertyValue() const;

private slots:

    void on_m_buttonBox_clicked(QAbstractButton *btn);

private:

    Ui::NewDynamicPropertyDialog *m_ui;
    QStringList m_reservedNames;

    typedef QMap<QString, QVariant> NameToValueMap;
    static const NameToValueMap &nameToValueMap();
};

}  // namespace qdesigner_internal

#endif // NEWDYNAMICPROPERTYDIALOG_P_H
