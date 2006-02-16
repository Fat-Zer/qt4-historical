/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech AS. All rights reserved.
**
** This file is part of the qt3to4 porting application of the Qt Toolkit.
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

#ifndef TEXTREPLACEMENT_H
#define TEXTREPLACEMENT_H

#include <QByteArray>
#include <QList>
#include <QtAlgorithms>

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
