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

#include "q3textedit_plugin.h"
#include "q3textedit_extrainfo.h"

#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>

#include <QtCore/qplugin.h>
#include <QtGui/QIcon>
#include <Qt3Support/Q3TextEdit>

Q3TextEditPlugin::Q3TextEditPlugin(QObject *parent)
        : QObject(parent), m_initialized(false)
{}

QString Q3TextEditPlugin::name() const
{ return QLatin1String("Q3TextEdit"); }

QString Q3TextEditPlugin::group() const
{ return QLatin1String("Qt 3 Support"); }

QString Q3TextEditPlugin::toolTip() const
{ return QString(); }

QString Q3TextEditPlugin::whatsThis() const
{ return QString(); }

QString Q3TextEditPlugin::includeFile() const
{ return QLatin1String("q3textedit.h"); }

QIcon Q3TextEditPlugin::icon() const
{ return QIcon(); }

bool Q3TextEditPlugin::isContainer() const
{ return false; }

QWidget *Q3TextEditPlugin::createWidget(QWidget *parent)
{ return new Q3TextEdit(parent); }

bool Q3TextEditPlugin::isInitialized() const
{ return m_initialized; }

void Q3TextEditPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);

    if (m_initialized)
        return;

    QExtensionManager *mgr = core->extensionManager();
    Q_ASSERT(mgr != 0);

    mgr->registerExtensions(new Q3TextEditExtraInfoFactory(core, mgr), Q_TYPEID(QDesignerExtraInfoExtension));

    m_initialized = true;
}

QString Q3TextEditPlugin::codeTemplate() const
{ return QString(); }

QString Q3TextEditPlugin::domXml() const
{ return QLatin1String("\
    <widget class=\"Q3TextEdit\" name=\"textEdit\">\
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


