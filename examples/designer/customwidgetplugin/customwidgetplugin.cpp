/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#include "analogclock.h"
#include "customwidgetplugin.h"

AnalogClockPlugin::AnalogClockPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void AnalogClockPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool AnalogClockPlugin::isInitialized() const
{
    return initialized;
}

QWidget *AnalogClockPlugin::createWidget(QWidget *parent)
{
    return new AnalogClock(parent);
}

QString AnalogClockPlugin::name() const
{
    return QLatin1String("AnalogClock");
}

QString AnalogClockPlugin::group() const
{
    return QLatin1String("Display Widgets [Examples]");
}

QIcon AnalogClockPlugin::icon() const
{
    return QIcon();
}

QString AnalogClockPlugin::toolTip() const
{
    return QString();
}

QString AnalogClockPlugin::whatsThis() const
{
    return QString();
}

bool AnalogClockPlugin::isContainer() const
{
    return false;
}

QString AnalogClockPlugin::domXml() const
{
    return QLatin1String("<widget class=\"AnalogClock\" name=\"analogClock\">\n"
                         " <property name=\"geometry\">\n"
                         "  <rect>\n"
                         "   <x>0</x>\n"
                         "   <y>0</y>\n"
                         "   <width>100</width>\n"
                         "   <height>100</height>\n"
                         "  </rect>\n"
                         " </property>\n"
                         " <property name=\"toolTip\" >\n"
                         "  <string>The current time</string>\n"
                         " </property>\n"
                         " <property name=\"whatsThis\" >\n"
                         "  <string>The analog clock widget displays "
                         "the current time.</string>\n"
                         " </property>\n"
                         "</widget>\n");
}

QString AnalogClockPlugin::includeFile() const
{
    return QLatin1String("analogclock.h");
}

QString AnalogClockPlugin::codeTemplate() const
{
    return QString();
}

Q_EXPORT_PLUGIN(AnalogClockPlugin)
