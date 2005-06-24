/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the qmake application of the Qt Toolkit.
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

#ifndef __MINGW_MAKE_H__
#define __MINGW_MAKE_H__

#include "winmakefile.h"

class MingwMakefileGenerator : public Win32MakefileGenerator
{
public:
    MingwMakefileGenerator();
    ~MingwMakefileGenerator();
private:
    void writeMingwParts(QTextStream &);
    void writeLibsPart(QTextStream &t);
    bool writeMakefile(QTextStream &);
    void writeObjectsPart(QTextStream &t);
    void writeBuildRulesPart(QTextStream &t);
    void writeRcFilePart(QTextStream &t);
    void init();

    virtual bool findLibraries();
    void fixTargetExt();

    bool init_flag;
    QString objectsLinkLine;
};

inline MingwMakefileGenerator::~MingwMakefileGenerator()
{ }

#endif /* __MINGW_MAKE_H__ */
