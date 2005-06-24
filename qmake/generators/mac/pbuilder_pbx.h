/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the qmake application of the Qt Toolkit.
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

#ifndef __PBUILDER_PBX_H__
#define __PBUILDER_PBX_H__

#include "unixmake.h"

class ProjectBuilderMakefileGenerator : public UnixMakefileGenerator
{
    QString pbx_dir;
    int pbuilderVersion() const;
    bool writeSubDirs(QTextStream &);
    bool writeMakeParts(QTextStream &);
    bool writeMakefile(QTextStream &);

    QString pbxbuild();
    QMap<QString, QString> keys;
    QString keyFor(const QString &file);
    QString fixForOutput(const QString &file);
    QString fixListForOutput(const QString &where);
    int     reftypeForFile(const QString &where);
    QString projectSuffix() const;

    enum IDE_TYPE { MAC_XCODE, MAC_PBUILDER };
    IDE_TYPE ideType() const;

public:
    ProjectBuilderMakefileGenerator();
    ~ProjectBuilderMakefileGenerator();

    virtual bool supportsMetaBuild() { return false; }
    virtual bool openOutput(QFile &, const QString &) const;
protected:
    bool doPrecompiledHeaders() const { return false; }
    virtual bool doDepends() const { return false; } //never necesary
};

inline ProjectBuilderMakefileGenerator::~ProjectBuilderMakefileGenerator()
{ }


#endif /* __PBUILDER_PBX_H__ */
