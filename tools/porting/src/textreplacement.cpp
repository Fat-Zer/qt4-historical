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

#include "textreplacement.h"
#include <iostream>
using namespace std;

bool TextReplacements::insert(QByteArray newText, int insertPosition, int currentLenght)
{
    //bubble sort the new replacement into the list
    int i;
    for(i=0; i<textReplacementList.size(); ++i) {
        if (insertPosition == textReplacementList.at(i).insertPosition)
            return false; // multiple replacements on the same insertPosition is not allowed.
        if(insertPosition < textReplacementList.at(i).insertPosition)
            break;  //we found the right position
    }
    //++i;
  //  cout << "inserting new text " << newText.constData() << endl;
    // %s at %d overwriting %d bytes at list pos %d\n", newText.constData(), insertPosition, currentLenght, i);
    TextReplacement rep;
    rep.newText=newText;
    rep.insertPosition=insertPosition;
    rep.currentLenght=currentLenght;

    textReplacementList.insert(i, rep);
    return true;
}

void TextReplacements::clear()
{
    textReplacementList.clear();
}

QByteArray TextReplacements::apply(QByteArray current)
{
    QByteArray newData=current;
    int i;
    int replacementOffset=0;

    for(i=0; i<textReplacementList.size(); ++i) {
        TextReplacement rep=textReplacementList.at(i);
        //printf("applying new text %s insert at %d overwriting %d bytes \n", rep.newText.constData(), rep.insertPosition, rep.currentLenght);
        newData.remove(rep.insertPosition+replacementOffset, rep.currentLenght);
        newData.insert(rep.insertPosition+replacementOffset, rep.newText);

        //modify all remaining replacements if we change the document length
        replacementOffset+=(rep.newText.size() - rep.currentLenght);
    }

    return newData;
}

TextReplacements &TextReplacements::operator+=(const TextReplacements &other)
{
    foreach(TextReplacement rep, other.replacements()) {
        insert(rep.newText, rep.insertPosition, rep.currentLenght);
    }
    return *this;
}
