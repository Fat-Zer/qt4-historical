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

#include <qdecorationplugin_qws.h>
#include <qdecorationwindows_qws.h>

class DecorationWindows : public QDecorationPlugin
{
public:
    DecorationWindows();

    QStringList keys() const;
    QDecoration *create(const QString&);
};

DecorationWindows::DecorationWindows()
: QDecorationPlugin()
{
}

QStringList DecorationWindows::keys() const
{
    QStringList list;
    list << "Windows";
    return list;
}

QDecoration* DecorationWindows::create(const QString& s)
{
    if (s.toLower() == "windows")
        return new QDecorationWindows();

    return 0;
}

Q_EXPORT_PLUGIN(DecorationWindows)
