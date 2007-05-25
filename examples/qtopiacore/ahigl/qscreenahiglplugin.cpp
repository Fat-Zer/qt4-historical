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

#include "qscreenahigl_qws.h"

#include <QScreenDriverPlugin>
#include <QStringList>

class QAhiGLScreenPlugin : public QScreenDriverPlugin
{
public:
    QAhiGLScreenPlugin();

    QStringList keys() const;
    QScreen *create(const QString&, int displayId);
};

QAhiGLScreenPlugin::QAhiGLScreenPlugin()
    : QScreenDriverPlugin()
{
}

QStringList QAhiGLScreenPlugin::keys() const
{
    return (QStringList() << "ahigl");
}

QScreen* QAhiGLScreenPlugin::create(const QString& driver, int displayId)
{
    if (driver.toLower() != "ahigl")
        return 0;

    return new QAhiGLScreen(displayId);
}

Q_EXPORT_STATIC_PLUGIN(QAhiGLScreen)
Q_EXPORT_PLUGIN2(qahiglscreen, QAhiGLScreenPlugin)
