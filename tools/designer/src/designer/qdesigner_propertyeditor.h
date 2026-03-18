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

#ifndef QDESIGNER_PROPERTYEDITOR_H
#define QDESIGNER_PROPERTYEDITOR_H

#include "qdesigner_toolwindow.h"

class QDesignerWorkbench;

class QDesignerPropertyEditor: public QDesignerToolWindow
{
    Q_OBJECT
public:
    QDesignerPropertyEditor(QDesignerWorkbench *workbench);
    virtual ~QDesignerPropertyEditor();

    virtual QRect geometryHint() const;

protected:
    virtual void showEvent(QShowEvent *event);
};

#endif // QDESIGNER_PROPERTYEDITOR_H
