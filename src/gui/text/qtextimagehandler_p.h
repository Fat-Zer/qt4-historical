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

#ifndef QTEXTIMAGEHANDLER_P_H
#define QTEXTIMAGEHANDLER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qobject.h>
#include <qabstracttextdocumentlayout.h>

#include "qtextdocument_p.h"

class QTextImageFormat;

class Q_GUI_EXPORT QTextImageHandler : public QObject,
                          public QTextObjectInterface
{
    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)
public:
    explicit QTextImageHandler(QObject *parent = 0);

    virtual QSizeF intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format);
    virtual void drawObject(QPainter *p, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format);

    typedef QImage (*ExternalImageLoaderFunction)(const QString &name, const QString &context);
    static ExternalImageLoaderFunction externalLoader;
};

#endif // QTEXTIMAGEHANDLER_P_H
