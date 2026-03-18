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
    TextReplacements includeDirectiveReplacements();

    PreprocessorCache &preprocessorCache;
    const QList<TokenReplacement*> tokenReplacementRules;
    const QHash<QByteArray, QByteArray> headerReplacements;

    ReplaceToken replaceToken;
    Tokenizer tokenizer;    //used by includeAnalyse

    QSet<QByteArray> qt4HeaderNames;
    QSet<QByteArray> m_usedQtModules;
};

class IncludeDirectiveReplace : public Rpp::RppTreeWalker
{
public:
    IncludeDirectiveReplace(const Rpp::Source *source, const QHash<QByteArray, QByteArray> &headerReplacements);
    TextReplacements getReplacements();
private:
    void evaluateIncludeDirective(const Rpp::IncludeDirective *directive);
    const QHash<QByteArray, QByteArray> headerReplacements;
    TextReplacements replacements;
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
