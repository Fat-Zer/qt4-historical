/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#include "gradients.h"

#include <QApplication>

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(gradients);

    QApplication app(argc, argv);

    GradientWidget gradientWidget(0);
    QStyle *arthurStyle = new ArthurStyle();
    gradientWidget.setStyle(arthurStyle);
    QList<QWidget *> widgets = qFindChildren<QWidget *>(&gradientWidget);
    foreach (QWidget *w, widgets)
        w->setStyle(arthurStyle);
    gradientWidget.show();

    return app.exec();
}
