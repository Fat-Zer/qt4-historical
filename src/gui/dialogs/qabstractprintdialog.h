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

#ifndef QABSTRACTPRINTDIALOG_H
#define QABSTRACTPRINTDIALOG_H

#include <QtGui/qdialog.h>

class QAbstractPrintDialogPrivate;
class QPrinter;

class Q_GUI_EXPORT QAbstractPrintDialog : public QDialog
{
    Q_DECLARE_PRIVATE(QAbstractPrintDialog)

public:
    enum PrintRange {
        AllPages,
        Selection,
        PageRange
    };

    enum PrintDialogOption {
        None                    = 0x0000,
        PrintToFile             = 0x0001,
        PrintSelection          = 0x0002,
        PrintPageRange          = 0x0004,
        PrintCollateCopies      = 0x0010
    };

    Q_DECLARE_FLAGS(PrintDialogOptions, PrintDialogOption)

    explicit QAbstractPrintDialog(QPrinter *printer, QWidget *parent = 0);

    virtual int exec() = 0;

    void addEnabledOption(PrintDialogOption option);
    void setEnabledOptions(PrintDialogOptions options);
    PrintDialogOptions enabledOptions() const;
    bool isOptionEnabled(PrintDialogOption option) const;

    void setPrintRange(PrintRange range);
    PrintRange printRange() const;

    void setMinMax(int min, int max);
    int minPage() const;
    int maxPage() const;

    void setFromTo(int fromPage, int toPage);
    int fromPage() const;
    int toPage() const;

    QPrinter *printer() const;

protected:
    QAbstractPrintDialog(QAbstractPrintDialogPrivate &ptr, QPrinter *printer, QWidget *parent = 0);

private:
    Q_DISABLE_COPY(QAbstractPrintDialog)
};

#endif // QABSTRACTPRINTDIALOG_H
