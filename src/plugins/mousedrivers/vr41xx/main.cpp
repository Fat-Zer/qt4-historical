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

#include <qmousedriverplugin_qws.h>
#include <qmousevr41xx_qws.h>

QT_BEGIN_NAMESPACE

class QVr41xxMouseDriver : public QMouseDriverPlugin
{
public:
    QVr41xxMouseDriver();

    QStringList keys() const;
    QWSMouseHandler* create(const QString &driver, const QString &device);
};

QVr41xxMouseDriver::QVr41xxMouseDriver()
    : QMouseDriverPlugin()
{
}

QStringList QVr41xxMouseDriver::keys() const
{
    return (QStringList() << QLatin1String("VR41xx"));
}

QWSMouseHandler* QVr41xxMouseDriver::create(const QString &driver,
                                            const QString &device)
{
    if (driver.compare(QLatin1String("VR41xx"), Qt::CaseInsensitive))
        return 0;
    return new QWSVr41xxMouseHandler(driver, device);
}

Q_EXPORT_PLUGIN2(qwsvr41xxmousehandler, QVr41xxMouseDriver)

QT_END_NAMESPACE
