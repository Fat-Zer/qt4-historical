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

#include <QtGui>

#include "droparea.h"

DropArea::DropArea(QWidget *parent)
    : QLabel(parent)
{
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    clear();
}

void DropArea::dragEnterEvent(QDragEnterEvent *event)
{
    setText(tr("<drop content>"));
    setBackgroundRole(QPalette::Highlight);

    event->acceptProposedAction();
    emit changed(event->mimeData());
}

void DropArea::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void DropArea::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasImage()) {
        setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
    } else if (mimeData->hasHtml()) {
        setText(mimeData->html());
        setTextFormat(Qt::RichText);
    } else if (mimeData->hasText()) {
        setText(mimeData->text());    
        setTextFormat(Qt::PlainText);
    } else {
        setText(tr("Cannot display data"));
    }

    setBackgroundRole(QPalette::Dark);
    event->acceptProposedAction();
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    clear();
    event->accept();
}

void DropArea::clear()
{
    setText(tr("<drop content>"));
    setBackgroundRole(QPalette::Dark);

    emit changed();
}

QPixmap DropArea::extractPixmap(const QByteArray &data, const QString &format)
{
    QList<QByteArray> imageFormats = QImageReader::supportedImageFormats();
    QPixmap pixmap;

    foreach (QByteArray imageFormat, imageFormats) {
        if (format.mid(6) == QString(imageFormat)) {
            pixmap.loadFromData(data, imageFormat);
            break;
        }
    }
    return pixmap;
}
