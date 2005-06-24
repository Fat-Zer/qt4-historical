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

#ifndef WRITEINCLUDES_H
#define WRITEINCLUDES_H

#include "treewalker.h"
#include <qmap.h>
#include <qstring.h>

class QTextStream;
class Driver;
class Uic;

struct Option;

struct WriteIncludes : public TreeWalker
{
    WriteIncludes(Uic *uic);

    void acceptUI(DomUI *node);
    void acceptWidget(DomWidget *node);
    void acceptLayout(DomLayout *node);
    void acceptSpacer(DomSpacer *node);

//
// custom widgets
//
    void acceptCustomWidgets(DomCustomWidgets *node);
    void acceptCustomWidget(DomCustomWidget *node);

//
// include hints
//
    void acceptIncludes(DomIncludes *node);
    void acceptInclude(DomInclude *node);

private:
    void add(const QString &className);

private:
    Uic *uic;
    Driver *driver;
    QTextStream &output;
    const Option &option;

    QMap<QString, bool> m_includes;
    QMap<QString, bool> m_customWidgets;
    QMap<QString, QString> m_classToHeader;
    QMap<QString, QString> m_oldHeaderToNewHeader;
};

#endif // WRITEINCLUDES_H
