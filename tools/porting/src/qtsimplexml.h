/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the qt3to4 porting application of the Qt Toolkit.
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
