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

#ifndef QSCRIPTVALUE_P_H
#define QSCRIPTVALUE_P_H

#include "qscriptvaluefwd_p.h"

#ifndef QT_NO_SCRIPT

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

inline QScriptValuePrivate::QScriptValuePrivate()
{
    ref.init();
}

inline QScriptValuePrivate *QScriptValuePrivate::create()
{
    return new QScriptValuePrivate();
}

inline QScriptValuePrivate *QScriptValuePrivate::get(const QScriptValue &value)
{
    return const_cast<QScriptValuePrivate*>(value.d_func());
}

inline QScriptValueImpl QScriptValuePrivate::valueOf(const QScriptValue &value)
{
    const QScriptValuePrivate *p = value.d_func();
    if (!p)
        return QScriptValueImpl();
    return p->value;
}

inline void QScriptValuePrivate::init(QScriptValue &value, QScriptValuePrivate *p)
{
    Q_ASSERT(value.d_ptr == 0);
    value.d_ptr = p;
    value.d_ptr->ref.ref();
}

inline QScriptValueImplList QScriptValuePrivate::toImplList(const QScriptValueList &lst)
{
    QScriptValueImplList result;
    QScriptValueList::const_iterator it;
    for (it = lst.constBegin(); it != lst.constEnd(); ++it)
        result.append(valueOf(*it));
    return result;
}

#endif // QT_NO_SCRIPT
#endif
