/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the linguist application of the Qt Toolkit.
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

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <qdialog.h>
#include "ui_finddialog.h"

class FindDialog : public QDialog, public Ui::FindDialog
{
    Q_OBJECT
public:
    enum {SourceText = 0x1, Translations = 0x2, Comments = 0x4};

    FindDialog(QWidget *parent = 0);

signals:
    void findNext(const QString& text, int where, bool matchCase);

private slots:
    void emitFindNext();
};

#endif
