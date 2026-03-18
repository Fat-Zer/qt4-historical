/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt3Support module of the Qt Toolkit.
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

#ifndef Q3SIGNAL_H
#define Q3SIGNAL_H

#ifndef QT_H
#include "QtCore/qvariant.h"
#include "QtCore/qobject.h"
#endif // QT_H

QT_MODULE(Qt3SupportLight)

class Q_COMPAT_EXPORT Q3Signal : public QObject
{
    Q_OBJECT

public:
    Q3Signal(QObject *parent=0, const char *name=0);
    ~Q3Signal();

    bool	connect(const QObject *receiver, const char *member);
    bool	disconnect(const QObject *receiver, const char *member=0);

    void	activate();

    bool	isBlocked()	 const		{ return QObject::signalsBlocked(); }
    void	block(bool b)		{ QObject::blockSignals(b); }
#ifndef QT_NO_VARIANT
    void	setParameter(int value);
    int		parameter() const;
#endif

#ifndef QT_NO_VARIANT
    void	setValue(const QVariant &value);
    QVariant	value() const;
#endif
signals:
#ifndef QT_NO_VARIANT
    void signal(const QVariant&);
#endif
    void intSignal(int);

private:
    Q_DISABLE_COPY(Q3Signal)

#ifndef QT_NO_VARIANT
    QVariant val;
#endif

};

#endif // Q3SIGNAL_H
