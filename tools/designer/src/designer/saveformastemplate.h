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

#ifndef SAVEFORMASTEMPLATE_H
#define SAVEFORMASTEMPLATE_H

#include "ui_saveformastemplate.h"

class QDesignerFormWindowInterface;

class SaveFormAsTemplate: public QDialog
{
    Q_OBJECT
public:
    SaveFormAsTemplate(QDesignerFormWindowInterface *formWindow, QWidget *parent = 0);
    virtual ~SaveFormAsTemplate();

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void updateOKButton(const QString &str);
    void checkToAddPath(int itemIndex);

private:
    Ui::SaveFormAsTemplate ui;
    QDesignerFormWindowInterface *m_formWindow;
    int m_addPathIndex;
};

#endif // SAVEFORMASTEMPLATE_H
