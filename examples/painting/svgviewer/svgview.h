/****************************************************************************
**
** Copyright (C) 2005-2006 Trolltech ASA. All rights reserved.
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

#ifndef SVGVIEW_H
#define SVGVIEW_H

#include <QWidget>
#include <QImage>
#ifndef QT_NO_OPENGL
#include <QGLWidget>
#endif

class QPaintEvent;
class QSvgRenderer;
class QWheelEvent;

class SvgRasterView : public QWidget
{
    Q_OBJECT
public:
    SvgRasterView(const QString &file, QWidget *parent=0);

    virtual QSize sizeHint() const;

protected slots:
    void poluteImage();
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    QSvgRenderer *doc;
    QImage buffer;
    bool m_dirty;
};

class SvgNativeView : public QWidget
{
    Q_OBJECT
public:
    SvgNativeView(const QString &file, QWidget *parent=0);

    virtual QSize sizeHint() const;
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    QSvgRenderer *doc;
};

#ifndef QT_NO_OPENGL
class SvgGLView : public QGLWidget
{
    Q_OBJECT
public:
    SvgGLView(const QString &file, QWidget *parent=0);

    virtual QSize sizeHint() const;
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    QSvgRenderer *doc;
};
#endif

#endif
