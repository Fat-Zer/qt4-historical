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
** (or its successors, if any) and the KDE Free Qt Foundation. 
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
#ifndef QPAGESETUPWIDGET_H
#define QPAGESETUPWIDGET_H

#include "qglobal.h"

#ifndef QT_NO_PRINTDIALOG

#include <ui_qpagesetupwidget.h>

QT_BEGIN_NAMESPACE

class QPrinter;
class QPagePreview;
class QCUPSSupport;

class QPageSetupWidget : public QWidget {
    Q_OBJECT
public:
    QPageSetupWidget(QWidget *parent = 0);
    QPageSetupWidget(QPrinter *printer, QWidget *parent = 0);
    void setPrinter(QPrinter *printer);
    /// copy information from the widget and apply that to the printer.
    void setupPrinter() const;
    void selectPrinter(QCUPSSupport *m_cups);
    void selectPdfPsPrinter(const QPrinter *p);

private slots:
    void _q_pageOrientationChanged();
    void _q_paperSizeChanged();
    void unitChanged(int item);
    void setTopMargin(double newValue);
    void setBottomMargin(double newValue);
    void setLeftMargin(double newValue);
    void setRightMargin(double newValue);

private:
    Ui::QPageSetupWidget widget;
    QPagePreview *m_pagePreview;
    QPrinter *m_printer;
    qreal m_leftMargin;
    qreal m_topMargin;
    qreal m_rightMargin;
    qreal m_bottomMargin;
    QSizeF m_paperSize;
    qreal m_currentMultiplier;
    bool m_blockSignals;
    QCUPSSupport *m_cups;
};

QT_END_NAMESPACE

#endif // QT_NO_PRINTDIALOG
#endif
