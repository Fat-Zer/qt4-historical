/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the qt3to4 porting application of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QTSIMPLEXML_H
#define QTSIMPLEXML_H

#include <QString>
#include <QMultiMap>
#include <QMap>

class QDomDocument;
class QDomElement;
class QDomNode;
class QIODevice;

class QtSimpleXml
{
public:
    QtSimpleXml(const QString &name = QString());

    QString name() const;
    QString text() const;
    int numChildren() const;
    bool isValid() const;

    const QtSimpleXml &operator [](int index) const;
    QtSimpleXml &operator [](int index);
    QtSimpleXml &operator [](const QString &key);
    QtSimpleXml &operator =(const QString &text);

    void setAttribute(const QString &key, const QString &value);
    QString attribute(const QString &key);

    bool setContent(const QString &content);
    bool setContent(QIODevice *device);
    QString errorString() const;

    QDomDocument toDomDocument() const;
    QDomElement toDomElement(QDomDocument *doc) const;
private:
    void parse(QDomNode node);

    QtSimpleXml *parent;

    QMultiMap<QString, QtSimpleXml *> children;
    QMap<QString, QString> attr;

    QString s;
    QString n;
    bool valid;

    QString errorStr;
};

#endif
