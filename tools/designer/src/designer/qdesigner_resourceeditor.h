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

#ifndef QDESIGNER_RESOURCEEDITOR_H
#define QDESIGNER_RESOURCEEDITOR_H

#include "qdesigner_toolwindow.h"

class QDesignerWorkbench;
class QDesignerAbstractFormWindowInterface;

class QDesignerResourceEditor: public QDesignerToolWindow
{
    Q_OBJECT
public:
    QDesignerResourceEditor(QDesignerWorkbench *workbench);
    virtual ~QDesignerResourceEditor();

    virtual QRect geometryHint() const;
};

#endif // QDESIGNER_RESOURCEEDITOR_H
