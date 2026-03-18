/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
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
