/****************************************************************************
**
** Copyright (C) 2007-2007 Trolltech ASA. All rights reserved.
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

#include <QtGui>
#include <QtScript>
#include "prototypes.h"

Q_DECLARE_METATYPE(QListWidgetItem*)
Q_DECLARE_METATYPE(QListWidget*)

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QScriptEngine engine;

    ListWidgetItemPrototype lwiProto;
    engine.setDefaultPrototype(qMetaTypeId<QListWidgetItem*>(),
                               engine.newQObject(&lwiProto));

    ListWidgetPrototype lwProto;
    engine.setDefaultPrototype(qMetaTypeId<QListWidget*>(),
                               engine.newQObject(&lwProto));

    QListWidget listWidget;
    engine.globalObject().setProperty("listWidget",
                                      engine.newQObject(&listWidget));

    QFile file(":/code.js");
    file.open(QIODevice::ReadOnly);
    QScriptValue result = engine.evaluate(file.readAll());
    file.close();
    if (engine.hasUncaughtException()) {
        int lineNo = engine.uncaughtExceptionLineNumber();
        qWarning() << "line" << lineNo << ":" << result.toString();
    }

    return app.exec();
}
