/****************************************************************************
**
** Copyright (C) 2005-2006 Trolltech AS. All rights reserved.
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

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include "glwidget.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QGLFormat f = QGLFormat::defaultFormat();
    f.setSampleBuffers(true);
    QGLFormat::setDefaultFormat(f);
    if (!QGLFormat::hasOpenGL()) {
	QMessageBox::information(0, "OpenGL samplebuffers",
				 "This system does not support OpenGL.",
				 QMessageBox::Ok);
        return 0;
    }

    GLWidget widget(0);

    if (!widget.format().sampleBuffers()) {
	QMessageBox::information(0, "OpenGL samplebuffers",
				 "This system does not have sample buffer support.",
				 QMessageBox::Ok);
        return 0;
    }

    widget.resize(640, 480);
    widget.show();

    return a.exec();
}

