/****************************************************************************
**
** Copyright (C) 2004-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#include <QtGui/qapplication.h>
#include <QtDBus/qdbusconnection.h>
#include "qdbusviewer.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStringList arguments = app.arguments();
    if (arguments.contains("--help")) {
        printf("Arguments:\n");
        printf("    --system    Use system bus\n");
        printf("    --help      This help\n");
        return 0;
    }

    bool showSystemBus = app.arguments().contains(QLatin1String("--system"));

    QDBusViewer viewer(showSystemBus ? QDBusConnection::systemBus() : QDBusConnection::sessionBus());
    viewer.show();

    return app.exec();
}

