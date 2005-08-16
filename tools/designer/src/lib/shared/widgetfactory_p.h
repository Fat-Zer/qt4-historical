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


#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include "shared_global_p.h"
#include "pluginmanager_p.h"

#include <QtDesigner/QDesignerWidgetFactoryInterface>

#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QPointer>

class QObject;
class QWidget;
class QLayout;
class QDesignerFormEditorInterface;
class QDesignerCustomWidgetInterface;

class QT_SHARED_EXPORT WidgetFactory: public QDesignerWidgetFactoryInterface
{
public:
    WidgetFactory(QDesignerFormEditorInterface *core, QObject *parent = 0);
    ~WidgetFactory();

    virtual QWidget* containerOfWidget(QWidget *widget) const;
    virtual QWidget* widgetOfContainer(QWidget *widget) const;

    virtual QWidget *createWidget(const QString &className, QWidget *parentWidget) const;
    virtual QLayout *createLayout(QWidget *widget, QLayout *layout, int type) const;

    virtual bool isPassiveInteractor(QWidget *widget);
    virtual void initialize(QObject *object) const;

    virtual QDesignerFormEditorInterface *core() const;

    static const char* classNameOf(QObject* o);

public slots:
    void loadPlugins();

private:
    QDesignerFormEditorInterface *m_core;
    QMap<QString, QDesignerCustomWidgetInterface*> m_customFactory;

    static QPointer<QWidget> *m_lastPassiveInteractor;
    static bool m_lastWasAPassiveInteractor;
};

#endif // WIDGETFACTORY_H
