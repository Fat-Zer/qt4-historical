/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Linguist of the Qt Toolkit.
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

#include "metatranslator.h"
#include <stdio.h>

// defined in numberh.cpp
extern int applyNumberHeuristic( MetaTranslator *tor );
// defined in sametexth.cpp
extern int applySameTextHeuristic( MetaTranslator *tor );

typedef QList<MetaTranslatorMessage> TML;

/*
  Merges two MetaTranslator objects into the first one. The first one
  is a set of source texts and translations for a previous version of
  the internationalized program; the second one is a set of fresh
  source texts newly extracted from the source code, without any
  translation yet.
*/

void merge( MetaTranslator *tor, const MetaTranslator *virginTor, bool verbose, bool noObsolete )
{
    int known = 0;
    int neww = 0;
    int obsoleted = 0;
    int untranslatedObsoleted = 0;
    TML all = tor->messages();
    TML::Iterator it;

    /*
      The types of all the messages from the vernacular translator
      are updated according to the virgin translator.
    */
    for ( it = all.begin(); it != all.end(); ++it ) {
        MetaTranslatorMessage::Type newType;
        MetaTranslatorMessage m = *it;

        // skip context comment
        if ( !QByteArray((*it).sourceText()).isEmpty() ) {
            if ( !virginTor->contains((*it).context(), (*it).sourceText(),
                                      (*it).comment()) ) {
                newType = MetaTranslatorMessage::Obsolete;
                if ( m.type() != MetaTranslatorMessage::Obsolete )
                    obsoleted++;
            } else {
                switch ( m.type() ) {
                case MetaTranslatorMessage::Finished:
                default:
                    newType = MetaTranslatorMessage::Finished;
                    known++;
                    break;
                case MetaTranslatorMessage::Unfinished:
                    newType = MetaTranslatorMessage::Unfinished;
                    known++;
                    break;
                case MetaTranslatorMessage::Obsolete:
                    newType = MetaTranslatorMessage::Unfinished;
                    neww++;
                }
            }

            if (newType == MetaTranslatorMessage::Obsolete && m.translation().isEmpty()) {
                ++untranslatedObsoleted;
            }

            if ( newType != m.type() ) {
                m.setType( newType );
                tor->insert( m );
            }
        }
    }

    /*
      Messages found only in the virgin translator are added to the
      vernacular translator. Among these are all the context comments.
    */
    all = virginTor->messages();

    for ( it = all.begin(); it != all.end(); ++it ) {
        if ( !tor->contains((*it).context(), (*it).sourceText(),
                            (*it).comment()) ) {
            tor->insert( *it );
            if ( !QByteArray((*it).sourceText()).isEmpty() )
                neww++;
        }
    }

    /*
      The same-text heuristic handles cases where a message has an
      obsolete counterpart with a different context or comment.
    */
    int sameTextHeuristicCount = applySameTextHeuristic( tor );

    /*
      The number heuristic handles cases where a message has an
      obsolete counterpart with mostly numbers differing in the
      source text.
    */
    int sameNumberHeuristicCount = applyNumberHeuristic( tor );

    if ( verbose ) {
        int totalFound = neww + known;
        fprintf( stderr, "    Found %d source text%s (%d new and %d already existing)\n",
            totalFound, totalFound == 1 ? "" : "s", neww, known);

        if (obsoleted) {
            if (noObsolete) {
                fprintf( stderr, "    Removed %d obsolete entr%s\n", 
                        obsoleted, obsoleted == 1 ? "y" : "ies" );
            } else {
                int total = obsoleted - untranslatedObsoleted;
                fprintf( stderr, "    Kept %d obsolete translation%s\n", 
                        total, total == 1 ? "" : "s" );

                fprintf( stderr, "    Removed %d obsolete untranslated entr%s\n", 
                        untranslatedObsoleted, untranslatedObsoleted == 1 ? "y" : "ies" );

            }
        }

        if (sameNumberHeuristicCount) 
            fprintf( stderr, "    Number heuristic provided %d translation%s\n", 
                sameNumberHeuristicCount, sameNumberHeuristicCount == 1 ? "" : "s" );
        if (sameTextHeuristicCount) 
            fprintf( stderr, "    Same-text heuristic provided %d translation%s\n", 
                sameTextHeuristicCount, sameTextHeuristicCount == 1 ? "" : "s" );

    }
}
