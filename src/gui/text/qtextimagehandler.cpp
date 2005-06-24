/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the text module of the Qt Toolkit.
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


#include "qtextimagehandler_p.h"

#include <qtextformat.h>
#include <qpainter.h>
#include <qpixmapcache.h>
#include <qdebug.h>
#include <private/qtextengine_p.h>
#include <qpalette.h>
#include <qtextbrowser.h>

// set by the mime source factory in Qt3Compat
QTextImageHandler::ExternalImageLoaderFunction QTextImageHandler::externalLoader = 0;

static QPixmap getPixmap(QTextDocument *doc, const QTextImageFormat &format)
{
    QPixmap pm;

    const bool hasWidth = format.hasProperty(QTextFormat::ImageWidth);
    const int width = qRound(format.width());
    const bool hasHeight = format.hasProperty(QTextFormat::ImageHeight);
    const int height = qRound(format.height());

    QString name = format.name();
    const QVariant data = doc->resource(QTextDocument::ImageResource, name);
    if (data.type() == QVariant::Pixmap || data.type() == QVariant::Image) {
        pm = qvariant_cast<QPixmap>(data);
    } else if (data.type() == QVariant::ByteArray) {
        pm.loadFromData(data.toByteArray());
    }

    if (pm.isNull()) {
        QTextBrowser *browser = qobject_cast<QTextBrowser *>(doc->parent());
        QString context;
        if (browser)
            context = browser->source().toString();
        QImage img;
        if (QTextImageHandler::externalLoader)
            img = QTextImageHandler::externalLoader(name, context);

        if (img.isNull()) // try direct loading
            if (name.isEmpty() || !img.load(name))
                return QPixmap(":/trolltech/styles/commonstyle/images/file-16.png");
        pm = QPixmap::fromImage(img);
        doc->addResource(QTextDocument::ImageResource, name, pm);
    }

    qreal scale = 1.0;
    QPaintDevice *pdev = doc->documentLayout()->paintDevice();
    if (pdev && !pm.isNull())
        scale = qreal(pdev->logicalDpiY()) / qreal(pm.logicalDpiY());

    QSize size = pm.size();
    if (hasWidth)
        size.setWidth(width);
    if (hasHeight)
        size.setHeight(height);

    size *= scale;

    if (size.isValid() && pm.size() != size)
        pm = pm.scaled(size);

    return pm;
}

QTextImageHandler::QTextImageHandler(QObject *parent)
    : QObject(parent)
{
}

QSizeF QTextImageHandler::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    Q_UNUSED(posInDocument)
    const QTextImageFormat imageFormat = format.toImageFormat();

    return getPixmap(doc, imageFormat).size();
}

void QTextImageHandler::drawObject(QPainter *p, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    Q_UNUSED(posInDocument)
    const QTextImageFormat imageFormat = format.toImageFormat();
    const QPixmap pixmap = getPixmap(doc, imageFormat);

    p->drawPixmap(rect, pixmap, pixmap.rect());
}

