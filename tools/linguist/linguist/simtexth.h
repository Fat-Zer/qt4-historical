/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the linguist application of the Qt Toolkit.
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

#ifndef SIMTEXTH_H
#define SIMTEXTH_H

#include <qstring.h>
#include <qlist.h>

class MetaTranslator;

struct Candidate {
    QString source;
    QString target;

    Candidate() { }
    Candidate( const QString& source0, const QString& target0 )
	: source( source0 ), target( target0 ) { }
};

inline bool operator==( const Candidate& c, const Candidate& d ) {
    return c.target == d.target && c.source == d.source;
}
inline bool operator!=( const Candidate& c, const Candidate& d ) {
    return !operator==( c, d );
}

typedef QList<Candidate> CandidateList;

CandidateList similarTextHeuristicCandidates( const MetaTranslator *tor,
					      const char *text,
					      int maxCandidates );

#endif
