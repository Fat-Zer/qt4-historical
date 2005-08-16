/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#ifndef VIEW3D_H
#define VIEW3D_H

#include <QtGui/QWidget>

class QScrollBar;
class QGLWidget;
class FormWindow;

class View3DWidget;

class View3D : public QWidget
{
    Q_OBJECT

public:
    View3D(FormWindow *form_window, QWidget *parent);

public slots:
    void updateForm();

private:
    View3DWidget *m_3d_widget;
    FormWindow *m_form_window;

    void addWidget(int depth, QWidget *w);
    void addTexture(QWidget *w);
};

#endif // VIEW3D_H

