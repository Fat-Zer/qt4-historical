/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QTEXTDOCUMENTFRAGMENT_P_H
#define QTEXTDOCUMENTFRAGMENT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qtextdocument.h"
#include "qtexthtmlparser_p.h"
#include "qtextdocument_p.h"

#include <qlist.h>
#include <qmap.h>
#include <qpointer.h>
#include <qvarlengtharray.h>
#include <qdatastream.h>

class QTextDocumentFragmentPrivate;

class QTextImportHelper
{
public:
    QTextImportHelper(QTextDocumentFragmentPrivate *docFragment, QTextDocumentPrivate *priv);

    void appendFragments(int pos, int endPos);
    int appendFragment(int pos, int endPos, int objectIndex = -1);
    int convertFormatIndex(const QTextFormat &oldFormat, int objectIndexToSet = -1);
    inline int convertFormatIndex(int oldFormatIndex, int objectIndexToSet = -1)
    { return convertFormatIndex(priv->formatCollection()->format(oldFormatIndex), objectIndexToSet); }

private:
    QTextDocumentFragmentPrivate *docFragment;
    QTextDocumentPrivate *priv;
    QTextFormatCollection &formatCollection;
    const QString originalText;
    QMap<int, int> objectIndexMap;
};

class QTextDocumentFragmentPrivate
{
public:
    enum MarkerValues { FragmentStart = 1, FragmentEnd = 2 };

    QTextDocumentFragmentPrivate() : hasTitle(false), containsCompleteDocument(false), setMarkerForHtmlExport(false) {}
    QTextDocumentFragmentPrivate(const QTextCursor &cursor);

    void insert(QTextCursor &cursor) const;

    void appendText(const QString &text, int formatIdx, int blockIdx = -2);

    QMap<int, int> fillFormatCollection(QTextFormatCollection *collection) const;

    // ### TODO: merge back into one big vector.

    struct TextFragment
    {
        TextFragment()
            : position(0), size(0),
              charFormat(-1), blockFormat(-2) {}
        qint32 position;
        quint32 size;
        qint32 charFormat;
        qint32 blockFormat;
    };
    typedef QVector<TextFragment> FragmentVector;

    FragmentVector fragments;

    QString localBuffer;

    QTextFormatCollection formatCollection;

    qint8 hasTitle;
    QString title;

    QTextFrameFormat rootFrameFormat;

    uint containsCompleteDocument : 1;
    uint setMarkerForHtmlExport : 1;
};

class QTextHTMLImporter : public QTextHtmlParser
{
    struct Table;
public:
    QTextHTMLImporter(QTextDocumentFragmentPrivate *d, const QString &html);

    void import();

private:
    bool closeTag(int i);

    Table scanTable(int tableNodeIdx) const;

    void appendBlock(const QTextBlockFormat &format, QTextCharFormat charFmt = QTextCharFormat(), const QChar &separator = QChar::ParagraphSeparator);
    void appendText(QString text, QTextCharFormat format);
    inline void appendImage(const QTextImageFormat &format)
    { appendText(QString(QChar::ObjectReplacementCharacter), format); }

    QTextDocumentFragmentPrivate *d;
    QVector<int> listReferences;
    int indent;

    // insert a named anchor the next time we emit a char format,
    // either in a block or in regular text
    bool setNamedAnchorInNextOutput;
    QString namedAnchor;

    struct Table
    {
        Table() : tableIndex(-1), currentColumnCount(0), currentRow(-1) {}
        int tableIndex; // objectIndex
        int currentColumnCount;
        int columns;
        QVector<int> rowSpanCellsPerRow;
        int currentRow;
    };
    QVector<Table> tables;
};

#endif // QTEXTDOCUMENTFRAGMENT_P_H
