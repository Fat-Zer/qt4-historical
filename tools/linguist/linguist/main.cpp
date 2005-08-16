/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the linguist application of the Qt Toolkit.
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

#include "trwindow.h"

#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <qtextcodec.h>
#include <qtranslator.h>
#include <qsettings.h>
#include <qsplashscreen.h>
#include <qcursor.h>
#include <qlocale.h>

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(linguist);

    QApplication app(argc, argv);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QString lang = QLocale::system().name();
    lang.chop(3); //remove country
    QTranslator translator(0);
    translator.load(QString("linguist_") + lang, ".");

    app.installTranslator(&translator);

    app.setOrganizationName("Trolltech");
    app.setApplicationName("Linguist");
    QString keybase("4.0/");
    QSettings config;

    QRect r(QApplication::desktop()->screenGeometry());
    r.setX(config.value(keybase + "Geometry/MainwindowX", r.x()).toInt());
    r.setY(config.value(keybase + "Geometry/MainwindowY", r.y()).toInt());
    r.setWidth(config.value(keybase + "Geometry/MainwindowWidth", r.width()).toInt());
    r.setHeight(config.value(keybase + "Geometry/MainwindowHeight", r.height()).toInt());

    QSplashScreen *splash = 0;
    splash = new QSplashScreen(QPixmap(":/images/splash.png"));
    splash->setAttribute(Qt::WA_DeleteOnClose);
    splash->show();

    TrWindow tw;

    if (config.value(keybase + "Geometry/MainwindowMaximized", false).toBool())
        tw.showMaximized();
    else
        tw.show();

    if (splash)
        splash->finish(&tw);

    if (app.argc() > 1)
        tw.openFile(QString(app.argv()[app.argc() - 1]));

    QApplication::restoreOverrideCursor();

    return app.exec();
}
