/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include "qpagesetupdialog.h"

#include <qhash.h>
#include <private/qapplication_p.h>
#include <private/qprintengine_mac_p.h>
#include <private/qabstractpagesetupdialog_p.h>

#ifndef QT_NO_PRINTDIALOG

QT_BEGIN_NAMESPACE

class QPageSetupDialogPrivate : public QAbstractPageSetupDialogPrivate
{
    Q_DECLARE_PUBLIC(QPageSetupDialog)
public:
    QPageSetupDialogPrivate() : ep(0), upp(0), sheetBlocks(false), acceptStatus(false) {}
    ~QPageSetupDialogPrivate() {
        if (upp) {
            DisposePMSheetDoneUPP(upp);
            upp = 0;
        }
        sheetCallbackMap.remove(ep->session);
    }
    static void pageSetupDialogSheetDoneCallback(PMPrintSession printSession, WindowRef /*documentWindow*/, Boolean accepted) {
        QPageSetupDialogPrivate *priv = sheetCallbackMap.value(printSession);
        if (!priv) {
            qWarning("%s:%d: QPageSetupDialog::exec: Could not retrieve data structure, "
                     "you most likely now have an infinite modal loop", __FILE__, __LINE__);
            return;
        }
        priv->sheetBlocks = false;
        priv->acceptStatus = accepted;
    }
    QMacPrintEnginePrivate *ep;
    PMSheetDoneUPP upp;
    bool sheetBlocks;
    Boolean acceptStatus;
    static QHash<PMPrintSession, QPageSetupDialogPrivate*> sheetCallbackMap;
};

QHash<PMPrintSession, QPageSetupDialogPrivate*> QPageSetupDialogPrivate::sheetCallbackMap;

QPageSetupDialog::QPageSetupDialog(QPrinter *printer, QWidget *parent)
    : QAbstractPageSetupDialog(*(new QPageSetupDialogPrivate), printer, parent)
{
    Q_D(QPageSetupDialog);
    QMacPrintEngine *engine = static_cast<QMacPrintEngine *>(d->printer->paintEngine());
    d->ep = static_cast<QMacPrintEnginePrivate *>(engine->d_ptr);
}

int QPageSetupDialog::exec()
{
    Q_D(QPageSetupDialog);

    if (d->printer->outputFormat() != QPrinter::NativeFormat)
        return Rejected;

    QMacPrintEngine *engine = static_cast<QMacPrintEngine *>(d->printer->paintEngine());
    QMacPrintEnginePrivate *ep = static_cast<QMacPrintEnginePrivate *>(engine->d_ptr);

    // If someone is reusing a QPrinter object, the end released all our old
    // information. In this case, we must reinitialize.
    if (ep->session == 0)
        ep->initialize();

    { //simulate modality
        // First, see if we should use a sheet.
        QWidget *parent = parentWidget();
        if (parent && parent->isVisible()) {
            WindowRef windowRef = qt_mac_window_for(parent);
            WindowClass wclass;
            GetWindowClass(windowRef, &wclass);
            if (!isOptionEnabled(QPageSetupDialog::DontUseSheet)
                    && (wclass == kDocumentWindowClass || wclass == kFloatingWindowClass
                        || wclass == kMovableModalWindowClass)) {
                // Yes, we can use a sheet
                if (!d->upp)
                    d->upp = NewPMSheetDoneUPP(QPageSetupDialogPrivate::pageSetupDialogSheetDoneCallback);
                d->sheetCallbackMap.insert(d->ep->session, d);
                PMSessionUseSheets(d->ep->session, qt_mac_window_for(parentWidget()), d->upp);
                d->sheetBlocks = true;
            }
        }
	QWidget modal_widg(0, Qt::Window);
        modal_widg.setObjectName(QLatin1String(__FILE__ "__modal_dlg"));
        modal_widg.createWinId();
	QApplicationPrivate::enterModal(&modal_widg);
    QApplicationPrivate::native_modal_dialog_active = true;
        PMSessionPageSetupDialog(ep->session, ep->format, &d->acceptStatus);
        while (d->sheetBlocks) {
            qApp->processEvents(QEventLoop::WaitForMoreEvents);
        }
	QApplicationPrivate::leaveModal(&modal_widg);
    QApplicationPrivate::native_modal_dialog_active = false;
    }
    return d->acceptStatus ? Accepted : Rejected;
}

QT_END_NAMESPACE

#endif QT_NO_PRINTDIALOG

