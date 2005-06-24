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
#ifndef __METAMAKEFILE_H__
#define __METAMAKEFILE_H__

class QMakeProject;
class MakefileGenerator;
#include <qlist.h>
#include <qstring.h>

class MetaMakefileGenerator
{
protected:
    MetaMakefileGenerator(QMakeProject *p) : project(p) { }
    QMakeProject *project;

public:

    virtual ~MetaMakefileGenerator();

    static MetaMakefileGenerator *createMetaGenerator(QMakeProject *);
    static MakefileGenerator *createMakefileGenerator(QMakeProject *proj, bool noIO = false);

    inline QMakeProject *projectFile() const { return project; }

    virtual bool init() = 0;
    virtual int type() const { return -1; }
    virtual bool write(const QString &) = 0;
};

#endif /* __METAMAKEFILE_H__ */
