/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#ifndef Q3SYNTAXHIGHLIGHTER_H
#define Q3SYNTAXHIGHLIGHTER_H

#include "QtGui/qfont.h"
#include "QtGui/qcolor.h"
#include "QtCore/qstring.h"

class Q3TextEdit;
class Q3SyntaxHighlighterInternal;
class Q3SyntaxHighlighterPrivate;
class Q3TextParagraph;

class Q_COMPAT_EXPORT Q3SyntaxHighlighter
{
    friend class Q3SyntaxHighlighterInternal;

public:
    Q3SyntaxHighlighter(Q3TextEdit *textEdit);
    virtual ~Q3SyntaxHighlighter();

    virtual int highlightParagraph(const QString &text, int endStateOfLastPara) = 0;

    void setFormat(int start, int count, const QFont &font, const QColor &color);
    void setFormat(int start, int count, const QColor &color);
    void setFormat(int start, int count, const QFont &font);
    Q3TextEdit *textEdit() const { return edit; }

    void rehighlight();

    int currentParagraph() const;

private:
    Q3TextParagraph *para;
    Q3TextEdit *edit;
    Q3SyntaxHighlighterPrivate *d;

};

#endif
