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

#ifndef PHRASE_H
#define PHRASE_H

#include <qstring.h>
#include <qlist.h>

class Phrase
{
public:
    Phrase() { }
    Phrase(const QString &source, const QString &target,
	    const QString &definition, int sc = -1);

    QString source() const {return s;}
    void setSource(const QString &ns) {s = ns;}
    QString target() const {return t;}
    void setTarget(const QString &nt) {t = nt;}
    QString definition() const {return d;}
    void setDefinition (const QString &nd) {d = nd;}
    int shortcut() const {return shrtc;}

private:
    int shrtc;
    QString s;
    QString t;
    QString d;
};

bool operator==(const Phrase &p, const Phrase &q);
inline bool operator!=(const Phrase &p, const Phrase &q) {
    return !(p == q);
}

class PhraseBook : public QList<Phrase>
{
public:
    PhraseBook() { }

    bool load(const QString &filename);
    bool save(const QString &filename) const;
    QString fileName() const {return fn;}
private:
    QString fn;
};

#endif
