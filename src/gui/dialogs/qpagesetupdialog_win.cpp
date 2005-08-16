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

#include "qpagesetupdialog.h"

#include <qapplication.h>

#include <private/qprintengine_win_p.h>
#include <private/qabstractpagesetupdialog_p.h>

class QPageSetupDialogPrivate : public QAbstractPageSetupDialogPrivate
{
};

QPageSetupDialog::QPageSetupDialog(QPrinter *printer, QWidget *parent)
    : QAbstractPageSetupDialog(*(new QPageSetupDialogPrivate), printer, parent)
{

}



int QPageSetupDialog::exec()
{
    Q_D(QPageSetupDialog);
    QWin32PrintEngine *engine = static_cast<QWin32PrintEngine*>(d->printer->paintEngine());
    QWin32PrintEnginePrivate *ep = static_cast<QWin32PrintEnginePrivate *>(engine->d_ptr);

    PAGESETUPDLG psd;
    memset(&psd, 0, sizeof(PAGESETUPDLG));
    psd.lStructSize = sizeof(PAGESETUPDLG);
    psd.hDevMode = ep->devMode;
    HGLOBAL *tempDevNames = ep->createDevNames();
    psd.hDevNames = tempDevNames;

    QWidget *parent = parentWidget();
    parent = parent ? parent->window() : qApp->activeWindow();
    psd.hwndOwner = parent ? parent->winId() : 0;

    QRect paperRect = d->printer->paperRect();
    QRect pageRect = d->printer->pageRect();

    psd.rtMargin.left   = paperRect.left() - pageRect.left();
    psd.rtMargin.top    = paperRect.top() - pageRect.top();
    psd.rtMargin.right  = paperRect.right() - pageRect.right();
    psd.rtMargin.bottom = paperRect.bottom() - pageRect.bottom();

    psd.Flags = PSD_INHUNDREDTHSOFMILLIMETERS
                | PSD_MARGINS;

    bool result = PageSetupDlg(&psd);

    // ### margins too...

    if (result) {
        ep->readDevnames(psd.hDevNames);
        ep->readDevmode(psd.hDevMode);
    }

    GlobalFree(tempDevNames);

    return result;
}
