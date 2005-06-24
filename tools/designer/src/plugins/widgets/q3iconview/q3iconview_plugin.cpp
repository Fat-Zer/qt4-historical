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

#include "q3iconview_plugin.h"
#include "q3iconview_extrainfo.h"

#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>

#include <QtCore/qplugin.h>
#include <QtGui/QIcon>
#include <Qt3Support/Q3IconView>

Q3IconViewPlugin::Q3IconViewPlugin(QObject *parent)
        : QObject(parent), m_initialized(false)
{}

QString Q3IconViewPlugin::name() const
{ return QLatin1String("Q3IconView"); }

QString Q3IconViewPlugin::group() const
{ return QLatin1String("Qt 3 Support"); }

QString Q3IconViewPlugin::toolTip() const
{ return QString(); }

QString Q3IconViewPlugin::whatsThis() const
{ return QString(); }

QString Q3IconViewPlugin::includeFile() const
{ return QLatin1String("q3iconview.h"); }

QIcon Q3IconViewPlugin::icon() const
{ return QIcon(); }

bool Q3IconViewPlugin::isContainer() const
{ return false; }

QWidget *Q3IconViewPlugin::createWidget(QWidget *parent)
{ return new Q3IconView(parent); }

bool Q3IconViewPlugin::isInitialized() const
{ return m_initialized; }

void Q3IconViewPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);

    if (m_initialized)
        return;

    QExtensionManager *mgr = core->extensionManager();
    Q_ASSERT(mgr != 0);

    mgr->registerExtensions(new Q3IconViewExtraInfoFactory(core, mgr), Q_TYPEID(QDesignerExtraInfoExtension));

    m_initialized = true;
}

QString Q3IconViewPlugin::codeTemplate() const
{ return QString(); }

QString Q3IconViewPlugin::domXml() const
{ return QLatin1String("\
    <widget class=\"Q3IconView\" name=\"iconView\">\
        <property name=\"geometry\">\
            <rect>\
                <x>0</x>\
                <y>0</y>\
                <width>100</width>\
                <height>80</height>\
            </rect>\
        </property>\
    </widget>\
    ");
}

