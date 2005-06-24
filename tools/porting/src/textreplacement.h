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

#ifndef TEXTREPLACEMENT_H
#define TEXTREPLACEMENT_H

#include <QByteArray>
#include <QList>
#include <qalgorithms.h>

class TextReplacement
{
public:
    QByteArray newText;
    int insertPosition;
    int currentLenght;    //lenght of the text that is going to be replaced.
    bool operator<(const TextReplacement &other) const
    {
        return  (insertPosition < other.insertPosition);
    }
};

class TextReplacements
{
public:
    /*
        creates a TextReplacement that inserts newText at insertPosition. currentLength bytes
        are overwritten in the original text. If there already is an insert at insertPosition,
        the insert will not be performed.

        insert maintains the TextReplacement list in sorted order.

        Returns true if the insert was successfull, false otherwise;
    */
    bool insert(QByteArray newText, int insertPosition, int currentLenght);
    void clear();
    QList<TextReplacement> replacements() const
    {
        return textReplacementList;
    }
    QByteArray apply(QByteArray current);

    TextReplacements &operator+=(const TextReplacements &other);

private:
    QList<TextReplacement> textReplacementList;
};

#endif
