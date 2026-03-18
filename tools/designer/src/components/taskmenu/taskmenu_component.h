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

#ifndef TASKMENU_COMPONENT_H
#define TASKMENU_COMPONENT_H

#include "taskmenu_global.h"
#include <QtDesigner/taskmenu.h>

#include <QtCore/QObject>

class QDesignerFormEditorInterface;

namespace qdesigner_internal {

class QT_TASKMENU_EXPORT TaskMenuComponent: public QObject
{
    Q_OBJECT
public:
    TaskMenuComponent(QDesignerFormEditorInterface *core, QObject *parent = 0);
    virtual ~TaskMenuComponent();

    QDesignerFormEditorInterface *core() const;

private:
    QDesignerFormEditorInterface *m_core;
};

}  // namespace qdesigner_internal

#endif // TASKMENU_COMPONENT_H
