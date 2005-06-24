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

#include <private/qapplication_p.h>
#include <private/qprintengine_mac_p.h>
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
    QMacPrintEngine *engine = static_cast<QMacPrintEngine *>(d->printer->paintEngine());
    QMacPrintEnginePrivate *ep = static_cast<QMacPrintEnginePrivate *>(engine->d_ptr);
    Boolean ret;
    { //simulate modality
	QWidget modal_widg(0, Qt::Window);
        modal_widg.setObjectName(QLatin1String(__FILE__ "__modal_dlg"));
	QApplicationPrivate::enterModal(&modal_widg);
        if (PMSessionPageSetupDialog(ep->session, ep->format, &ret) != noErr)
            ret = false;
	QApplicationPrivate::leaveModal(&modal_widg);
    }
    return ret ? Accepted : Rejected;
}
