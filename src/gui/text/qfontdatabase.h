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

#ifndef QFONTDATABASE_H
#define QFONTDATABASE_H

#include "QtGui/qwindowdefs.h"
#include "QtCore/qstring.h"
#include "QtGui/qfont.h"
#ifdef QT3_SUPPORT
#include "QtCore/qstringlist.h"
#include "QtCore/qlist.h"
#endif

QT_MODULE(Gui)

class QStringList;
template <class T> class QList;
struct QFontDef;
class QFontEngine;

class QFontDatabasePrivate;

class Q_GUI_EXPORT QFontDatabase
{
public:
    enum WritingSystem {
        Any,

        Latin,
        Greek,
        Cyrillic,
        Armenian,
        Hebrew,
        Arabic,
        Syriac,
        Thaana,
        Devanagari,
        Bengali,
        Gurmukhi,
        Gujarati,
        Oriya,
        Tamil,
        Telugu,
        Kannada,
        Malayalam,
        Sinhala,
        Thai,
        Lao,
        Tibetan,
        Myanmar,
        Georgian,
        Khmer,
        SimplifiedChinese,
        TraditionalChinese,
        Japanese,
        Korean,
        Vietnamese,

        Other,

        WritingSystemsCount
    };

    static QList<int> standardSizes();

    QFontDatabase();

    QList<WritingSystem> writingSystems() const;
    QStringList families(WritingSystem writingSystem = Any) const;
    QStringList styles(const QString &family) const;
    QList<int> pointSizes(const QString &family, const QString &style = QString());
    QList<int> smoothSizes(const QString &family, const QString &style);
    QString styleString(const QFont &font);

    QFont font(const QString &family, const QString &style, int pointSize) const;

    bool isBitmapScalable(const QString &family, const QString &style = QString()) const;
    bool isSmoothlyScalable(const QString &family, const QString &style = QString()) const;
    bool isScalable(const QString &family, const QString &style = QString()) const;
    bool isFixedPitch(const QString &family, const QString &style = QString()) const;

    bool italic(const QString &family, const QString &style) const;
    bool bold(const QString &family, const QString &style) const;
    int weight(const QString &family, const QString &style) const;

    static QString writingSystemName(WritingSystem writingSystem);
    static QString writingSystemSample(WritingSystem writingSystem);

private:
    static void createDatabase();
    static void parseFontName(const QString &name, QString &foundry, QString &family);
    static QFontEngine *findFont(int script, const QFontPrivate *fp,
                                 const QFontDef &request, int force_encoding_id = -1);

    friend struct QFontDef;
    friend class QFontPrivate;
    friend class QFontDialog;
    friend class QFontEngineMultiXLFD;

    QFontDatabasePrivate *d;
};


#endif // QFONTDATABASE_H
