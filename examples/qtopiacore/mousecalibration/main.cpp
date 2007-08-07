/****************************************************************************
**
** Copyright (C) 2006-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
** 
** Trolltech ASA (c) 2007
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QWSServer>

#include "calibration.h"
#include "scribblewidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv, QApplication::GuiServer);

    if (!QWSServer::mouseHandler())
        qFatal("No mouse handler installed");

    {
        QMessageBox message;
        message.setText("<p>Please press once at each of the marks "
                        "shown in the next screen.</p>"
                        "<p>This messagebox will timout after 10 seconds "
                        "if you are unable to close it.</p>");
        QTimer::singleShot(10 * 1000, &message, SLOT(accept()));
        message.exec();
    }

    Calibration cal;
    cal.exec();

    {
        QMessageBox message;
        message.setText("<p>The next screen will let you test the calibration "
                        "by drawing into a widget.</p><p>This program will "
                        "automatically close after 20 seconds.<p>");
        QTimer::singleShot(10 * 1000, &message, SLOT(accept()));
        message.exec();
    }

    ScribbleWidget scribble;
    scribble.showMaximized();
    scribble.show();

    app.setActiveWindow(&scribble);
    QTimer::singleShot(20 * 1000, &app, SLOT(quit()));

    return app.exec();
}

