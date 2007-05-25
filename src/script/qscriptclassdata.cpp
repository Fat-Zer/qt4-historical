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

#include "qscriptclassdata_p.h"

void QScriptClassData::mark(const QScriptValueImpl &, int)
{
}

bool QScriptClassData:: resolve(const QScriptValueImpl &, QScriptNameIdImpl *,
                                QScript::Member *, QScriptValueImpl *)
{
    return false;
}

bool QScriptClassData::get(const QScriptValueImpl &, const QScript::Member &,
                           QScriptValueImpl *)
{
    Q_ASSERT_X(false, "QScriptClassData::get()",
               "implement if resolveMember is implemented");
    return false;
}

bool QScriptClassData::put(QScriptValueImpl *, const QScript::Member &,
                           const QScriptValueImpl &)
{
    Q_ASSERT_X(false, "QScriptClassData::put()",
               "implement if resolveMember is implemented");
    return false;
}

bool QScriptClassData::removeMember(const QScriptValueImpl &,
                                    const QScript::Member &)
{
    return true;
}

int QScriptClassData::extraMemberCount(const QScriptValueImpl &)
{
    return 0;
}

bool QScriptClassData::extraMember(const QScriptValueImpl &,
                                   int, QScript::Member *)
{
    return false;
}
