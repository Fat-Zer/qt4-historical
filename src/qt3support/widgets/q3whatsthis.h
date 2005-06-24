/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef Q3WHATSTHIS_H
#define Q3WHATSTHIS_H

#include "QtGui/qcursor.h"
#include "QtGui/qwhatsthis.h"
#include "QtGui/qwidget.h"

class QToolButton;

class Q_COMPAT_EXPORT Q3WhatsThis: public QObject
{
    Q_OBJECT
public:
    Q3WhatsThis(QWidget *);
    ~Q3WhatsThis();
    bool eventFilter(QObject *, QEvent *);

    static inline void enterWhatsThisMode() { QWhatsThis::enterWhatsThisMode(); }
    static inline bool inWhatsThisMode() { return QWhatsThis::inWhatsThisMode(); }

    static inline void add(QWidget *w, const QString &s) { w->setWhatsThis(s); }
    static inline void remove(QWidget *w) { w->setWhatsThis(QString()); }
    static QToolButton * whatsThisButton(QWidget * parent);
    static inline void leaveWhatsThisMode(const QString& text = QString(), const QPoint& pos = QCursor::pos(), QWidget* w = 0)
        { QWhatsThis::showText(pos, text, w); }
    static inline void display(const QString& text, const QPoint& pos = QCursor::pos(), QWidget* w = 0)
        { QWhatsThis::showText(pos, text, w); }

    virtual QString text(const QPoint &);
    virtual bool clicked(const QString& href);

};

#endif // Q3WHATSTHIS_H
