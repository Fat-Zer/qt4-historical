/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the dialog module of the Qt Toolkit.
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

#ifndef QABSTRACTPAGESETUPDIALOG_H
#define QABSTRACTPAGESETUPDIALOG_H

#include "QtGui/qdialog.h"

class QAbstractPageSetupDialogPrivate;
class QPrinter;

class Q_GUI_EXPORT QAbstractPageSetupDialog : public QDialog
{
    Q_DECLARE_PRIVATE(QAbstractPageSetupDialog)

public:
    explicit QAbstractPageSetupDialog(QPrinter *printer, QWidget *parent = 0);
    QAbstractPageSetupDialog(QAbstractPageSetupDialogPrivate &ptr,
                             QPrinter *printer, QWidget *parent = 0);

    virtual int exec() = 0;

    QPrinter *printer();
};

#endif // QABSTRACTPAGESETUPDIALOG_H
