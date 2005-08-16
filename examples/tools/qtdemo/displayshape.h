/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#ifndef DISPLAYSHAPE_H
#define DISPLAYSHAPE_H

#include <QBrush>
#include <QFont>
#include <QHash>
#include <QPainterPath>
#include <QPen>
#include <QPointF>
#include <QSizeF>
#include <QWidget>

class DisplayShape
{
public:
    DisplayShape(const QPointF &position, const QSizeF &maxSize);
    virtual ~DisplayShape() {};

    virtual bool animate();
    virtual bool contains(const QString &key) const;
    virtual bool isInteractive() const;
    virtual QVariant metaData(const QString &key) const;
    virtual void paint(QPainter *painter) const;
    virtual QPointF position() const;
    virtual QPointF target() const;
    virtual QRectF rect() const;
    virtual QSizeF size() const;
    virtual void removeMetaData(const QString &key);
    virtual void setInteractive(bool enable);
    virtual void setMetaData(const QString &key, const QVariant &value);
    virtual void setPosition(const QPointF &point);
    virtual void setTarget(const QPointF &point);

protected:
    QHash<QString,QVariant> meta;
    QImage image;
    QPointF pos;
    QPointF targetPos;
    QSizeF maxSize;
    bool interactive;
};

class PanelShape : public DisplayShape
{
public:
    PanelShape(const QPainterPath &path, const QBrush &normal,
              const QBrush &highlighted, const QPen &pen,
              const QPointF &position, const QSizeF &maxSize);

    bool animate();
    void paint(QPainter *painter) const;
    QRectF rect() const;

private:
    QBrush brush;
    QBrush highlightedBrush;
    QBrush normalBrush;
    QPainterPath path;
    QPen pen;
};

class TitleShape : public DisplayShape
{
public:
    TitleShape(const QString &text, const QFont &font, const QPen &pen,
               const QPointF &position, const QSizeF &maxSize,
               Qt::Alignment alignment = Qt::AlignVCenter | Qt::AlignLeft);

    bool animate();
    void paint(QPainter *painter) const;
    QRectF rect() const;

private:
    QFont font;
    QString text;
    QPen pen;
    QRectF textRect;
    Qt::Alignment alignment;
};

class ImageShape : public DisplayShape
{
public:
    ImageShape(const QImage &original, const QPointF &position,
               const QSizeF &maxSize, int alpha = 0,
               Qt::Alignment alignment = Qt::AlignCenter);

    bool animate();
    void paint(QPainter *painter) const;
    QRectF rect() const;

private:
    void redraw();

    int alpha;
    QImage source;
    QPointF offset;
    Qt::Alignment alignment;
    qreal scale;
};

class DocumentShape : public DisplayShape
{
public:
    DocumentShape(const QString &text, const QFont &font, const QPen &pen,
                  const QPointF &position, const QSizeF &maxSize);
    ~DocumentShape();

    bool animate();
    void paint(QPainter *painter) const;
    QRectF rect() const;

private:
    qreal formatText();

    QFont font;
    QStringList paragraphs;
    QList<QTextLayout*> layouts;
    QPen pen;
};

#endif
