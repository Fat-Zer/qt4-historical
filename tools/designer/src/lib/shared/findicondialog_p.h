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

#ifndef FINDICONDIALOG_H
#define FINDICONDIALOG_H

#include "shared_global_p.h"

#include <QtGui/QDialog>

class QDesignerFormWindowInterface;
class QListWidgetItem;
class QModelIndex;

namespace Ui
{
    class FindIconDialog;
} // namespace Ui

class QT_SHARED_EXPORT FindIconDialog : public QDialog
{
    Q_OBJECT

public:
    FindIconDialog(QDesignerFormWindowInterface *form, QWidget *parent);
    virtual ~FindIconDialog();

    void setPaths(const QString &qrcPath, const QString &filePath);
    QString qrcPath() const;
    QString filePath() const;

private slots:
    void updateBoxes();
    void imageFileSelected(QListWidgetItem*);
    void browseFileDir();
    void setActiveBox();
    void resourceSelected(const QModelIndex&);
    void updateButtons();

private:
    enum InputBox { FileBox, ResourceBox };

    void activateBox(InputBox box);
    InputBox activeBox() const;

    Ui::FindIconDialog *ui;
    QString m_icon_file_name;
    QDesignerFormWindowInterface *m_form;
};

#endif // FINDICONDIALOG_H
