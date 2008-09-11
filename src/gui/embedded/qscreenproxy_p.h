/****************************************************************************
**
** Copyright (C) 2008-2008 Trolltech ASA. All rights reserved.
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

#ifndef QPROXYSCREENCURSOR_QWS_H
#define QPROXYSCREENCURSOR_QWS_H

#include <QtGui/qscreen_qws.h>

#ifndef QT_NO_QWS_PROXYSCREEN
#ifndef QT_NO_QWS_CURSOR

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class QSCreenCursor;
class QProxyScreenCursorPrivate;

class Q_GUI_EXPORT QProxyScreenCursor : public QScreenCursor
{
public:
    QProxyScreenCursor();
    ~QProxyScreenCursor();

    void setScreenCursor(QScreenCursor *cursor);
    QScreenCursor* screenCursor() const;

    void set(const QImage &image, int hotx, int hoty);
    void move(int x, int y);
    void show();
    void hide();

private:
    void configure();

    QScreenCursor *realCursor;
    QProxyScreenCursorPrivate *d_ptr;
};

QT_END_NAMESPACE
QT_END_HEADER

#endif // QT_NO_QWS_CURSOR
#endif // QT_NO_QWS_PROXYSCREEN
#endif // QPROXYSCREENCURSOR_QWS_H
