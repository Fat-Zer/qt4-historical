/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Linguist of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

/*  TRANSLATOR FindDialog

    Choose Edit|Find from the menu bar or press Ctrl+F to pop up the
    Find dialog
*/

#include "finddialog.h"

#include <qcheckbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwhatsthis.h>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    findWhat->setBuddy(led);

    connect(findNxt, SIGNAL(clicked()), this, SLOT(emitFindNext()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    resize(400, 1);
    setMaximumHeight(height());

    led->setFocus();
}

void FindDialog::emitFindNext()
{
    int where;
    if (sourceText != 0)
        where = (sourceText->isChecked() ? SourceText : 0) |
                (translations->isChecked() ? Translations : 0) |
                (comments->isChecked() ? Comments : 0);
    else
        where = Translations;
    emit findNext(led->text(), where, matchCase->isChecked());
}
