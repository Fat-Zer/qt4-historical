/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QHash>
#include <QString>
#include <QStringList>
#include <QTextBlock>
#include <QTextCharFormat>

class QTextDocument;

class Highlighter : public QObject
{
    Q_OBJECT
public:
    Highlighter(QObject *parent = 0);

    void addToDocument(QTextDocument *doc);
    void addMapping(const QString &pattern, const QTextCharFormat &format);

private slots:
    void highlight(int from, int removed, int added);

private:
    void highlightBlock(QTextBlock block);

    QHash<QString,QTextCharFormat> mappings;
};

#endif
