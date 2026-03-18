/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QPRINTER_P_H
#define QPRINTER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qglobal.h>
#ifdef QT3_SUPPORT
#include <qpointer.h>
#include <qprintdialog.h>
#endif

#ifndef QT_NO_PRINTER

class QPrintEngine;

class QPrinterPrivate
{
public:
    QPrinterPrivate()
        : printEngine(0)
#if defined(QT3_SUPPORT) && !(defined(QT_NO_PRINTDIALOG))
        , printDialog(0)
#endif
    {
    }

    QPrintEngine *printEngine;

#if defined(QT3_SUPPORT) && !(defined(QT_NO_PRINTDIALOG))
    QPointer<QPrintDialog> printDialog;
#endif
};

#endif // QT_NO_PRINTER

#endif // QPRINTER_P_H
