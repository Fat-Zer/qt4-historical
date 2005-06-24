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

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "treewalker.h"

class QTextStream;
class Driver;
class Uic;

struct Option;

struct Validator : public TreeWalker
{
    Validator(Uic *uic);

    void acceptUI(DomUI *node);
    void acceptWidget(DomWidget *node);

    void acceptLayoutItem(DomLayoutItem *node);
    void acceptLayout(DomLayout *node);

    void acceptActionGroup(DomActionGroup *node);
    void acceptAction(DomAction *node);

private:
    Driver *driver;
    QTextStream &output;
    const Option &option;
    Uic *uic;
};

#endif // VALIDATOR_H
