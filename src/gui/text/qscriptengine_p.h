/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the text module of the Qt Toolkit.
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

#ifndef QSCRIPTENGINE_P_H
#define QSCRIPTENGINE_P_H

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

#include "qtextengine_p.h"

class QString;
struct QGlyphLayout;
struct QCharAttributes;

struct QShaperItem {
    int script;
    const QString *string;
    int from;
    int length;
    QFontEngine *font;
    QGlyphLayout *glyphs;
    int num_glyphs; // in: available glyphs out: glyphs used/needed
    unsigned short *log_clusters;
    int flags;
};

// return true if ok.
typedef bool (*ShapeFunction)(QShaperItem *item);
//typedef void (*ShapeFunction)(int script, const QString &, int, int, QTextEngine *, QScriptItem *);
typedef void (*AttributeFunction)(int script, const QString &, int, int, QCharAttributes *);

struct q_scriptEngine {
    ShapeFunction shape;
    AttributeFunction charAttributes;
};

extern const q_scriptEngine qt_scriptEngines[];

#endif // QSCRIPTENGINE_P_H
