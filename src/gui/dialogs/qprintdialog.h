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

#ifndef QPRINTDIALOG_H
#define QPRINTDIALOG_H

#include "QtGui/qabstractprintdialog.h"

class QPrintDialogPrivate;
class QAbstractButton;
class QPrinter;

class Q_GUI_EXPORT QPrintDialog : public QAbstractPrintDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QPrintDialog)
public:
    explicit QPrintDialog(QPrinter *printer, QWidget *parent = 0);
    ~QPrintDialog();

#if defined (Q_OS_UNIX) && !defined (Q_OS_MAC) && defined (QT3_SUPPORT)
    void setPrinter(QPrinter *, bool = false);
    QPrinter *printer() const;
    void addButton(QPushButton *button);
#endif

    int exec();

private:
    Q_DISABLE_COPY(QPrintDialog)

// #if defined (Q_OS_UNIX) && !defined (Q_OS_MAC)
    Q_PRIVATE_SLOT(d_func(), void browseClicked())
    Q_PRIVATE_SLOT(d_func(), void okClicked())
    Q_PRIVATE_SLOT(d_func(), void printerOrFileSelected(QAbstractButton *))
    Q_PRIVATE_SLOT(d_func(), void landscapeSelected(int))
    Q_PRIVATE_SLOT(d_func(), void paperSizeSelected(int))
    Q_PRIVATE_SLOT(d_func(), void orientSelected(int))
    Q_PRIVATE_SLOT(d_func(), void pageOrderSelected(QAbstractButton *))
    Q_PRIVATE_SLOT(d_func(), void colorModeSelected(QAbstractButton *))
    Q_PRIVATE_SLOT(d_func(), void setNumCopies(int))
    Q_PRIVATE_SLOT(d_func(), void printRangeSelected(QAbstractButton *))
    Q_PRIVATE_SLOT(d_func(), void setFirstPage(int))
    Q_PRIVATE_SLOT(d_func(), void setLastPage(int))
    Q_PRIVATE_SLOT(d_func(), void fileNameEditChanged(const QString &text))
// #endif
};

#endif // QPRINTDIALOG_H
