/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the $MODULE$ of the Qt Toolkit.
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

#ifndef QSCRIPTVALUEITERATOR_H
#define QSCRIPTVALUEITERATOR_H

#include <QtScript/qscriptvalue.h>

#ifndef QT_NO_SCRIPT

QT_BEGIN_HEADER

QT_MODULE(Script)

class QString;

class QScriptValueIteratorPrivate;
class Q_SCRIPT_EXPORT QScriptValueIterator
{
public:
    QScriptValueIterator(const QScriptValue &value);
    ~QScriptValueIterator();

    bool hasNext() const;
    void next();

    bool hasPrevious() const;
    void previous();

    QString name() const;

    QScriptValue value() const;
    void setValue(const QScriptValue &value);

    QScriptValue::PropertyFlags flags() const;

    void remove();

    void toFront();
    void toBack();

    QScriptValueIterator& operator=(QScriptValue &value);

private:
    QScriptValueIteratorPrivate *d_ptr;

    Q_DECLARE_PRIVATE(QScriptValueIterator)
    Q_DISABLE_COPY(QScriptValueIterator)
};

QT_END_HEADER

#endif // QT_NO_SCRIPT
#endif // QSCRIPTVALUEITERATOR_H
