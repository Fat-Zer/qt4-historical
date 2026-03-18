/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
**
** This file is part of the qt3to4 porting application of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef CODEMODELATTRIBUTES_H
#define CODEMODELATTRIBUTES_H

#include "codemodelwalker.h"
#include "translationunit.h"

class CodeModelAttributes : public CodeModelWalker
{
public:
    void createAttributes(TranslationUnit translationUnit);
protected:
    void parseNameUse(CodeModel::NameUse *);
    void parseMember(CodeModel::Member *member);

    void createNameTypeAttribute(CodeModel::Member *member);
    void createNameTypeAttribute(CodeModel::NameUse *nameUse);

private:
    void createNameTypeAttributeAtIndex(TokenEngine::TokenAttributes *attributes,
                                        int index, CodeModel::Member *member);
    bool areAttributesEnabled(const TokenEngine::TokenAttributes *attributes) const;

    TranslationUnit  m_translationUnit;
};

#endif


