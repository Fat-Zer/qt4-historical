/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
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

#ifndef XFORM_H
#define XFORM_H

#include "arthurwidgets.h"

#include <QBasicTimer>
#include <QPolygonF>

class HoverPoints;
class QLineEdit;

class XFormView : public ArthurFrame
{
    Q_OBJECT

    Q_PROPERTY(bool animation READ animation WRITE setAnimation)
    Q_PROPERTY(double shear READ shear WRITE setShear)
    Q_PROPERTY(double rotation READ rotation WRITE setRotation)
    Q_PROPERTY(double scale READ scale WRITE setScale)

public:
    XFormView(QWidget *parent);
    void paint(QPainter *);
    void drawVectorType(QPainter *painter);
    void drawPixmapType(QPainter *painter);
    void drawTextType(QPainter *painter);
    QSize sizeHint() const { return QSize(500, 500); }

    void mousePressEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);
    HoverPoints *hoverPoints() { return pts; }

    QLineEdit *textEditor;

    bool animation() const { return timer.isActive(); }
    double shear() const { return m_shear; }
    double scale() const { return m_scale; }
    double rotation() const { return m_rotation; }
    void setShear(double s);
    void setScale(double s);
    void setRotation(double r);

public slots:
    void setAnimation(bool animate);
    void updateCtrlPoints(const QPolygonF &);
    void changeRotation(int rotation);
    void changeScale(int scale);
    void changeShear(int shear);

    void setVectorType();
    void setPixmapType();
    void setTextType();
    void reset();

signals:
    void rotationChanged(int rotation);
    void scaleChanged(int scale);
    void shearChanged(int shear);

protected:
    void timerEvent(QTimerEvent *e);
    void wheelEvent(QWheelEvent *);

private:
    enum XFormType { VectorType, PixmapType, TextType };

    QPolygonF ctrlPoints;
    HoverPoints *pts;
    double m_rotation;
    double m_scale;
    double m_shear;
    XFormType type;
    QPixmap pixmap;
    QBasicTimer timer;
};

class XFormWidget : public QWidget
{
    Q_OBJECT
public:
    XFormWidget(QWidget *parent);

private:
    XFormView *view;
};

#endif // XFORM_H
