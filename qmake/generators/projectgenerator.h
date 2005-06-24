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
#ifndef __PROJECTGENERATOR_H__
#define __PROJECTGENERATOR_H__

#include "makefile.h"

class ProjectGenerator : public MakefileGenerator
{
    bool init_flag;
    bool addFile(QString);
    bool addConfig(const QString &, bool add=true);
    QString getWritableVar(const QString &, bool fixPath=true);
protected:
    virtual void init();
    virtual bool writeMakefile(QTextStream &);
public:
    ProjectGenerator();
    ~ProjectGenerator();
    virtual bool supportsMetaBuild() { return false; }
    virtual bool openOutput(QFile &, const QString &) const;
};

inline ProjectGenerator::~ProjectGenerator()
{ }


#endif /* __PROJECTGENERATOR_H__ */
