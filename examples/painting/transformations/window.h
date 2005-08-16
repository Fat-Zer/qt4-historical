/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#ifndef WINDOW_H
#define WINDOW_H

#include <QList>
#include <QPainterPath>
#include <QWidget>

#include "renderarea.h"

class QComboBox;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

public slots:
    void operationChanged();
    void shapeSelected(int index);

private:
    void setupShapes();

    enum { NumTransformedAreas = 3 };
    RenderArea *originalRenderArea;
    RenderArea *transformedRenderAreas[NumTransformedAreas];
    QComboBox *shapeComboBox;
    QComboBox *operationComboBoxes[NumTransformedAreas];
    QList<QPainterPath> shapes;
};

#endif
