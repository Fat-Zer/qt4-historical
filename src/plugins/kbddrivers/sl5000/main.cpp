/****************************************************************************
**
** Copyright (C) 2008-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the plugins of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <qkbddriverplugin_qws.h>
#include <qkbdsl5000_qws.h>

QT_BEGIN_NAMESPACE

class QSL5000KbdDriver : public QKbdDriverPlugin
{
public:
    QSL5000KbdDriver();

    QStringList keys() const;
    QWSKeyboardHandler* create(const QString &driver, const QString &device);
};

QSL5000KbdDriver::QSL5000KbdDriver()
    : QKbdDriverPlugin()
{
}

QStringList QSL5000KbdDriver::keys() const
{
    return (QStringList() << QLatin1String("SL5000"));
}

QWSKeyboardHandler* QSL5000KbdDriver::create(const QString &driver,
                                             const QString &device)
{
    Q_UNUSED(device);
    if (driver.compare(QLatin1String("SL5000"), Qt::CaseInsensitive))
        return 0;
    return new QWSSL5000KeyboardHandler(driver);
}

Q_EXPORT_PLUGIN2(qwssl5000kbddriver, QSL5000KbdDriver)

QT_END_NAMESPACE
