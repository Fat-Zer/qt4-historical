/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#include "q3groupbox_plugin.h"

#include <Qt3Support/Q3GroupBox>
#include <QtGui/QLayout>
#include <QtCore/qplugin.h>

Q3GroupBoxPlugin::Q3GroupBoxPlugin(QObject *parent)
    : QObject(parent),
      m_initialized(false)
{
}

Q3GroupBoxPlugin::~Q3GroupBoxPlugin()
{
}


QString Q3GroupBoxPlugin::name() const
{
    return QLatin1String("Q3GroupBox");
}

QString Q3GroupBoxPlugin::group() const
{
    return QLatin1String("Qt 3 Support");
}

QString Q3GroupBoxPlugin::toolTip() const
{
    return QString();
}

QString Q3GroupBoxPlugin::whatsThis() const
{
    return QString();
}

QString Q3GroupBoxPlugin::includeFile() const
{
    return QLatin1String("Qt3Support/Q3GroupBox");
}

QIcon Q3GroupBoxPlugin::icon() const
{
    return QIcon();
}

bool Q3GroupBoxPlugin::isContainer() const
{
    return true;
}

QWidget *Q3GroupBoxPlugin::createWidget(QWidget *parent)
{
    Q3GroupBox *g = new Q3GroupBox(parent);
    g->setColumnLayout(0, Qt::Vertical);
    return g;
}

bool Q3GroupBoxPlugin::isInitialized() const
{
    return m_initialized;
}

void Q3GroupBoxPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);
    m_initialized = true;
}

