/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
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

#ifndef SVGWINDOW_H
#define SVGWINDOW_H

#include <QPoint>
#include <QScrollArea>
#include <QString>

class QKeyEvent;
class QMouseEvent;

class SvgWindow : public QScrollArea
{
public:
    enum RendererType { Native, OpenGL, Image };

    SvgWindow();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void openFile(const QString &file);
    void setRenderer(RendererType type = Native);
    void setHighQualityAntialiasing(bool highQualityAntialiasing);

private:
    QPoint mousePressPos;
    QPoint scrollBarValuesOnMousePress;
    QString currentPath;
    RendererType renderer;

    bool highQualityAntialiasing;
};

#endif
