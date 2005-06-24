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

#ifndef ABSTRACTWIDGETDATABASE_H
#define ABSTRACTWIDGETDATABASE_H

#include <QtDesigner/sdk_global.h>

#include <QtCore/QObject>
#include <QtCore/QList>

class QIcon;
class QString;
class QDesignerFormEditorInterface;

class QDesignerWidgetDataBaseItemInterface
{
public:
    virtual ~QDesignerWidgetDataBaseItemInterface() {}

    virtual QString name() const = 0;
    virtual void setName(const QString &name) = 0;

    virtual QString group() const = 0;
    virtual void setGroup(const QString &group) = 0;

    virtual QString toolTip() const = 0;
    virtual void setToolTip(const QString &toolTip) = 0;

    virtual QString whatsThis() const = 0;
    virtual void setWhatsThis(const QString &whatsThis) = 0;

    virtual QString includeFile() const = 0;
    virtual void setIncludeFile(const QString &includeFile) = 0;

    virtual QIcon icon() const = 0;
    virtual void setIcon(const QIcon &icon) = 0;

    virtual bool isCompat() const = 0;
    virtual void setCompat(bool compat) = 0;

    virtual bool isContainer() const = 0;
    virtual void setContainer(bool container) = 0;

    virtual bool isCustom() const = 0;
    virtual void setCustom(bool custom) = 0;

    virtual QString pluginPath() const = 0;
    virtual void setPluginPath(const QString &path) = 0;

    virtual bool isPromoted() const = 0;
    virtual void setPromoted(bool b) = 0;

    virtual QString extends() const = 0;
    virtual void setExtends(const QString &s) = 0;

    virtual void setDefaultPropertyValues(const QList<QVariant> &list) = 0;
    virtual QList<QVariant> defaultPropertyValues() const = 0;
};

class QT_SDK_EXPORT QDesignerWidgetDataBaseInterface: public QObject
{
    Q_OBJECT
public:
    QDesignerWidgetDataBaseInterface(QObject *parent = 0);
    virtual ~QDesignerWidgetDataBaseInterface();

    virtual int count() const;
    virtual QDesignerWidgetDataBaseItemInterface *item(int index) const;

    virtual int indexOf(QDesignerWidgetDataBaseItemInterface *item) const;
    virtual void insert(int index, QDesignerWidgetDataBaseItemInterface *item);
    virtual void append(QDesignerWidgetDataBaseItemInterface *item);

    virtual int indexOfObject(QObject *object, bool resolveName = true) const;
    virtual int indexOfClassName(const QString &className, bool resolveName = true) const;

    virtual QDesignerFormEditorInterface *core() const;

    bool isContainer(QObject *object, bool resolveName = true) const;
    bool isCustom(QObject *object, bool resolveName = true) const;

signals:
    void changed();

protected:
    QList<QDesignerWidgetDataBaseItemInterface *> m_items;
};

#endif // ABSTRACTWIDGETDATABASE_H
