/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
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

#ifndef GENERATOR_H
#define GENERATOR_H

#include "moc.h"

class Generator
{
    FILE *out;
    ClassDef *cdef;
public:
    Generator(FILE *outfile, ClassDef *classDef);
    void generateCode();
private:
    void generateClassInfos();
    void generateFunctions(QList<FunctionDef> &list, const char *functype, int type);
    void generateEnums(int index);
    void generateProperties();
    void generateMetacall();
    void generateSignal(FunctionDef *def, int index);

    int strreg(const char *); // registers a string and returns its id
    QList<QByteArray>strings;
    QByteArray purestSuperClass;
};

#endif // GENERATOR_H
