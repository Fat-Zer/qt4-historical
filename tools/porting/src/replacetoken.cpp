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

#include <QByteArray>
#include "replacetoken.h"
#include "tokenreplacements.h"
/*
    Add an entry to the tokenRuleLookup map for each token replacement rule.
*/
ReplaceToken::ReplaceToken(QList<TokenReplacement*> &tokenReplacementRules)
:tokenReplacementRules(tokenReplacementRules)
{
    foreach (TokenReplacement* rep, tokenReplacementRules) {
        QByteArray key = rep->getReplaceKey();
        if(!key.isEmpty()) {
            tokenRuleLookup.insert(key, rep);
        }
    }
}

TextReplacements ReplaceToken::getTokenTextReplacements(const TokenEngine::TokenContainer &container)
{
    TextReplacements textReplacements;

    int t=0;
    const int numTokens = container.count();
    while(t < numTokens) {
        QByteArray tokenText = container.text(t);
        bool changed = false;

        if(isPreprocessorDirective(tokenText)) {
            foreach(TokenReplacement *tokenReplacementRule, tokenReplacementRules) {
                if(!changed)
                    changed = tokenReplacementRule->doReplace(container, t, textReplacements);
                if(changed)
                    break;
            }
        } else if (isInterestingToken(tokenText.trimmed())) {
            foreach (TokenReplacement* value, tokenRuleLookup.values(tokenText)) {
                changed = value->doReplace(container, t, textReplacements);
                if(changed) {
                    goto end;
                }
            }
        }
    end:
        ++t;
    }
    return textReplacements;
}

bool ReplaceToken::isInterestingToken(const QByteArray &text)
{
    return !(text.isEmpty() || text==";" || text=="(" || text==")" || text=="{" || text=="}" || text=="="
            || text=="+=" || text=="-=" || text=="if" || text=="then" || text=="else"
    );
}

bool ReplaceToken::isPreprocessorDirective(const QByteArray &token)
{
    return (token[0]=='#');
}
