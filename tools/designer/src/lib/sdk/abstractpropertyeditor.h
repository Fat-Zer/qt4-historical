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

#ifndef ABSTRACTPROPERTYEDITOR_H
#define ABSTRACTPROPERTYEDITOR_H

#include <QtDesigner/sdk_global.h>

#include <QtGui/QWidget>

class QDesignerFormEditorInterface;
class QString;
class QVariant;

class QT_SDK_EXPORT QDesignerPropertyEditorInterface: public QWidget
{
    Q_OBJECT
public:
    QDesignerPropertyEditorInterface(QWidget *parent, Qt::WindowFlags flags = 0);
    virtual ~QDesignerPropertyEditorInterface();

    virtual QDesignerFormEditorInterface *core() const;

    virtual bool isReadOnly() const = 0;
    virtual QObject *object() const = 0;

    virtual QString currentPropertyName() const = 0;

signals:
    void propertyChanged(const QString &name, const QVariant &value);

public slots:
    virtual void setObject(QObject *object) = 0;
    virtual void setPropertyValue(const QString &name, const QVariant &value, bool changed = true) = 0;
    virtual void setReadOnly(bool readOnly) = 0;
};

#endif // ABSTRACTPROPERTYEDITOR_H
