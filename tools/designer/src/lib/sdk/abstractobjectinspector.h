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

#ifndef ABSTRACTOBJECTINSPECTOR_H
#define ABSTRACTOBJECTINSPECTOR_H

#include <QtDesigner/sdk_global.h>

#include <QtGui/QWidget>

class QDesignerFormEditorInterface;
class QDesignerFormWindowInterface;

class QT_SDK_EXPORT QDesignerObjectInspectorInterface: public QWidget
{
    Q_OBJECT
public:
    QDesignerObjectInspectorInterface(QWidget *parent, Qt::WindowFlags flags = 0);
    virtual ~QDesignerObjectInspectorInterface();

    virtual QDesignerFormEditorInterface *core() const;

public slots:
    virtual void setFormWindow(QDesignerFormWindowInterface *formWindow) = 0;
};

#endif // ABSTRACTOBJECTINSPECTOR_H
