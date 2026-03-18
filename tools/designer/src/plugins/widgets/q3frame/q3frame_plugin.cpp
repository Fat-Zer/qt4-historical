/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#include "q3frame_plugin.h"

#include <Qt3Support/Q3Frame>
#include <QtCore/qplugin.h>

Q3FramePlugin::Q3FramePlugin(QObject *parent)
    : QObject(parent),
      m_initialized(false)
{
}

Q3FramePlugin::~Q3FramePlugin()
{
}


QString Q3FramePlugin::name() const
{
    return QLatin1String("Q3Frame");
}

QString Q3FramePlugin::group() const
{
    return QLatin1String("Qt 3 Support");
}

QString Q3FramePlugin::toolTip() const
{
    return QString();
}

QString Q3FramePlugin::whatsThis() const
{
    return QString();
}

QString Q3FramePlugin::includeFile() const
{
    return QLatin1String("Qt3Support/Q3Frame");
}

QIcon Q3FramePlugin::icon() const
{
    return QIcon();
}

bool Q3FramePlugin::isContainer() const
{
    return true;
}

QWidget *Q3FramePlugin::createWidget(QWidget *parent)
{
    return new Q3Frame(parent);
}

bool Q3FramePlugin::isInitialized() const
{
    return m_initialized;
}

void Q3FramePlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);
    m_initialized = true;
}

