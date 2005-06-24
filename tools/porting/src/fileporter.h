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

#ifndef FILEPORTER_H
#define FILEPORTER_H

#include <QString>
#include <QSet>
#include <QMap>
#include "portingrules.h"
#include "replacetoken.h"
#include "filewriter.h"
#include "preprocessorcontrol.h"

class FilePorter
{
public:
    FilePorter(PreprocessorCache &preprocessorCache);
    void port(QString fileName);
    QSet<QByteArray> usedQtModules();
private:
    QByteArray loadFile(const QString &fileName);
    QByteArray includeAnalyse(QByteArray fileContents);

    PreprocessorCache &preprocessorCache;
    QList<TokenReplacement*> tokenReplacementRules;
    ReplaceToken replaceToken;
    Tokenizer tokenizer;    //used by includeAnalyse

    QSet<QByteArray> qt4HeaderNames;
    QSet<QByteArray> m_usedQtModules;
};

class IncludeDirectiveAnalyzer : public Rpp::RppTreeWalker
{
public:
    IncludeDirectiveAnalyzer(const TokenEngine::TokenContainer &fileContents);
    int insertPos();
    QSet<QByteArray> includedHeaders();
    QSet<QByteArray> usedClasses();
private:
    void evaluateIncludeDirective(const Rpp::IncludeDirective *directive);
    void evaluateIfSection(const Rpp::IfSection *ifSection);
    void evaluateText(const Rpp::Text *textLine);

    int insertTokenIndex;
    bool foundInsertPos;
    bool foundQtHeader;
    int ifSectionCount;

    const TokenEngine::TokenContainer &fileContents;
    Rpp::Source *source;
    TypedPool<Rpp::Item> mempool;
    QSet<QByteArray> m_includedHeaders;
    QSet<QByteArray> m_usedClasses;
};


#endif
