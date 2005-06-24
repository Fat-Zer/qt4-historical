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

#ifndef __METROWERKS_XML_H__
#define __METROWERKS_XML_H__

#include "makefile.h"

class MetrowerksMakefileGenerator : public MakefileGenerator
{
    bool createFork(const QString &f);
    bool fixifyToMacPath(QString &c, QString &v, bool exists=true);

    bool init_flag;

    bool writeMakeParts(QTextStream &);
    bool writeSubDirs(QTextStream &);

    bool writeMakefile(QTextStream &);
    QString findTemplate(const QString &file);
    void init();
public:
    MetrowerksMakefileGenerator();
    ~MetrowerksMakefileGenerator();

    bool supportsMetaBuild() { return false; }
    bool openOutput(QFile &file, const QString &build) const;
protected:
    virtual void processPrlFiles();
    virtual void processPrlVariable(const QString &var, const QStringList &l);
    virtual bool doDepends() const { return false; } //never necesary
};

inline MetrowerksMakefileGenerator::~MetrowerksMakefileGenerator()
{ }

#endif /* __METROWERKS_XML_H__ */
