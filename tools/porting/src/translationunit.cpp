/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the porting application of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "translationunit.h"
#include <iostream>

using namespace std;
using namespace TokenEngine;
using namespace CodeModel;
using namespace TokenStreamAdapter;

TranslationUnit::TranslationUnit()
{
    TokenSectionSequence empty;
    d = new TranslationUnitData(empty);
}

TranslationUnit::TranslationUnit(const TokenEngine::TokenSectionSequence &tokens)
{ d = new TranslationUnitData(tokens); }

TokenSectionSequence TranslationUnit::tokens() const
{ return d->tokens; }

void TranslationUnit::setCodeModel(NamespaceScope *globalScope)
{ d->globalScope = globalScope; }

NamespaceScope *TranslationUnit::codeModel()
{ return d->globalScope; }

TypedPool<CodeModel::Item> *TranslationUnit::codeModelMemoryPool()
{ return &d->codeModelMemoryPool; }



/*
    Performs C++ parsing and semantic analysis on a translation unit.
    Returns a TranslationUnit, which contains all the data.
*/
TranslationUnit TranslationUnitAnalyzer::analyze
        (const TokenSectionSequence &translationUnitTokens, int targetMaxASTNodes)
{
    TranslationUnit translationUnit(translationUnitTokens);
    CodeModel::NamespaceScope *codeModel =
        CodeModel::Create<CodeModel::NamespaceScope>(translationUnit.codeModelMemoryPool());
    translationUnit.setCodeModel(codeModel);

    // run lexical analysis
    QVector< ::Type> typeList = lexer.lex(translationUnitTokens);
    TokenStreamAdapter::TokenStream tokenStream(translationUnitTokens, typeList);

    Semantic semantic(codeModel, &tokenStream, translationUnit.codeModelMemoryPool());

    // parse and run semantic on the translation unit
    bool done = false;
    while(!done) {
        pool p;
        TranslationUnitAST *node = parser.parse(&tokenStream, &p, targetMaxASTNodes, done);
        semantic.parseTranslationUnit(node);
    }

    return translationUnit;
}
