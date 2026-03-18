/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
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

#ifndef REPLACETOKEN_H
#define REPLACETOKEN_H

#include <QList>
#include <QMultiMap>
#include "tokenengine.h"
#include "tokenreplacements.h"
#include "textreplacement.h"

class ReplaceToken
{
public:
    ReplaceToken(const QList<TokenReplacement*> &tokenReplacementRules);
    TextReplacements getTokenTextReplacements(const TokenEngine::TokenContainer &tokenContainer);
private:
    bool isInterestingToken(const QByteArray &token);
    bool isPreprocessorDirective(const QByteArray &token);
    QMultiMap<QByteArray, TokenReplacement*> tokenRuleLookup;
    const QList<TokenReplacement*> tokenReplacementRules;
};

#endif
