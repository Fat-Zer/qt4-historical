/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
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

#ifndef DOMIMAGE_H
#define DOMIMAGE_H

#include <QPixmap>
#include <QImage>
#include <QMetaType>

#include <qscriptengine.h>

class DomImage
{
public:
    DomImage();
    static void setup(QScriptEngine *e);

    int width() const;
    int height() const;

    QString src() const;
    void setSrc(const QString &src);

    QString name() const;

    static QScriptValue s_self;

    const QImage &image() const
    {
        return m_image;
    }
private:
    QImage  m_image;
    QString m_src;
    //attribute boolean         isMap;
    //attribute DOMString       longDesc;
    //attribute DOMString       useMap;
    //attribute DOMString       align;
    //attribute DOMString       alt;
    //attribute DOMString       border;
    //attribute long            vspace;
    //attribute long            hspace;
};

Q_DECLARE_METATYPE(DomImage)
Q_DECLARE_METATYPE(DomImage*)

#endif
