/****************************************************************************
**
** Copyright (C) 2004-2007 Trolltech ASA. All rights reserved.
** Copyright (C) 2001-2004 Roberto Raggi
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
** Trolltech ASA (c) 2007
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "codemodel.h"

#include <QList>
#include <QByteArray>
#include <QtDebug>

namespace CodeModel {

BuiltinType BuiltinType::Bool("bool", 0 );
BuiltinType BuiltinType::Void("void", 0 );
BuiltinType BuiltinType::Char("char", 0 );
BuiltinType BuiltinType::Short("short", 0 );
BuiltinType BuiltinType::Int("int", 0 );
BuiltinType BuiltinType::Long("long", 0 );
BuiltinType BuiltinType::Double("double", 0 );
BuiltinType BuiltinType::Float("float", 0 );
BuiltinType BuiltinType::Unsigned("unsigned", 0 );
BuiltinType BuiltinType::Signed("signed", 0 );

void Scope::addScope(Scope *scope)
{
    scope->setParent(this);
    m_scopes.add(scope);
}

void Scope::addType(Type *type)
{
    if (ClassType *klass = type->toClassType())
        klass->setParent(this);
    m_types.add(type);
}

void Scope::addMember(Member *member)
{
    member->setParent(this);
    m_members.add(member);
}

void Scope::addNameUse(NameUse *nameUse)
{
    nameUse->setParent(this);
    m_nameUses.add(nameUse);
}

} //namepsace CodeModel
