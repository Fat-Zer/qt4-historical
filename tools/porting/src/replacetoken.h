/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the porting application of the Qt Toolkit.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
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
    ReplaceToken(QList<TokenReplacement*> &tokenReplacementRules);
    TextReplacements getTokenTextReplacements(const TokenEngine::TokenContainer &tokenContainer);
private:
    bool isInterestingToken(const QByteArray &token);
    bool isPreprocessorDirective(const QByteArray &token);
    QMultiMap<QByteArray, TokenReplacement*> tokenRuleLookup;
    QList<TokenReplacement*> tokenReplacementRules;
};

#endif
