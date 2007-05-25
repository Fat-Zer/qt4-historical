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

#include <QtCore/QTextStream>

#ifndef QT_NO_SCRIPT

#include "qscriptasm_p.h"
#include "qscriptvalueimpl_p.h"
#include "qscriptengine_p.h"
#include "qscriptcontext_p.h"
#include "qscriptmember_p.h"
#include "qscriptobject_p.h"

const char *QScriptInstruction::opcode[] = {
#define STR(a) #a
#define Q_SCRIPT_DEFINE_OPERATOR(op) STR(i##op) ,
#include "instruction.table"
#undef Q_SCRIPT_DEFINE_OPERATOR
#undef STR
};

void QScriptInstruction::print(QTextStream &out) const
{
    out << opcode[op];

    if (! operand[0].isValid())
        return;

    out << '(' << operand[0].toString();

    if (operand[1].isValid())
        out << ", " << operand[1].toString();

    out << ')';
}

namespace QScript {

Code::Code():
    optimized(false),
    firstInstruction(0),
    lastInstruction(0)
{
}

Code::~Code()
{
    delete[] firstInstruction;
}

void Code::init(const CompilationUnit &compilation, NodePool *pool)
{
    optimized = false;
    const QVector<QScriptInstruction> ilist = compilation.instructions();
    firstInstruction = new QScriptInstruction[ilist.count()];
    lastInstruction = firstInstruction + ilist.count();
    qCopy(ilist.begin(), ilist.end(), firstInstruction);
    exceptionHandlers = compilation.exceptionHandlers();
    astPool = pool;
}

} // namespace QScript

#endif // QT_NO_SCRIPT
