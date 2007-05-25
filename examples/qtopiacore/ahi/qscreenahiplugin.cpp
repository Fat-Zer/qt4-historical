/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "qscreenahi_qws.h"

#include <QtGui/qscreendriverplugin_qws.h>
#include <QtCore/qstringlist.h>

class AhiScreenDriverPlugin : public QScreenDriverPlugin
{
public:
    AhiScreenDriverPlugin();

    QStringList keys() const;
    QScreen* create(const QString&, int displayId);
};

AhiScreenDriverPlugin::AhiScreenDriverPlugin()
    : QScreenDriverPlugin()
{
}

QStringList AhiScreenDriverPlugin::keys() const
{
    return (QStringList() << "ahi");
}

QScreen* AhiScreenDriverPlugin::create(const QString& driver, int displayId)
{
    if (driver.toLower() != "ahi")
        return 0;

    return new QAhiScreen(displayId);
}

Q_EXPORT_STATIC_PLUGIN(AhiScreenDriver)
Q_EXPORT_PLUGIN2(qahiscreendriver, AhiScreenDriverPlugin)
