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

#include <QApplication>
#include <QUiLoader>
#include <QtScript>
#include <QWidget>
#include <QFile>
#include <QMessageBox>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QScriptEngine engine;

    QFile scriptFile(":/calculator.js");
    scriptFile.open(QIODevice::ReadOnly);
    engine.evaluate(scriptFile.readAll());
    scriptFile.close();

    QUiLoader loader;
    QFile uiFile(":/calculator.ui");
    uiFile.open(QIODevice::ReadOnly);
    QWidget *ui = loader.load(&uiFile);
    uiFile.close();

    QScriptValue ctor = engine.evaluate("Calculator");
    QScriptValue scriptUi = engine.newQObject(ui);
    QScriptValue calc = ctor.construct(QScriptValueList() << scriptUi);

    ui->show();
    return app.exec();
}
