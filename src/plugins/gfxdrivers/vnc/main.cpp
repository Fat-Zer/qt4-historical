/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the plugins of the Qt Toolkit.
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

#include <qgfxdriverplugin_qws.h>
#include <qgfxvnc_qws.h>
#include <qstringlist.h>

class GfxVncDriver : public QGfxDriverPlugin
{
public:
    GfxVncDriver();

    QStringList keys() const;
    QScreen *create(const QString&, int displayId);
};

GfxVncDriver::GfxVncDriver()
: QGfxDriverPlugin()
{
}

QStringList GfxVncDriver::keys() const
{
    QStringList list;
    list << "VNC";
    return list;
}

QScreen* GfxVncDriver::create(const QString& driver, int displayId)
{
    if (driver.toLower() == "vnc")
        return new QVNCScreen(displayId);

    return 0;
}

Q_EXPORT_PLUGIN(GfxVncDriver)
