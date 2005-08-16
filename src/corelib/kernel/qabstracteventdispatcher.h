/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the core module of the Qt Toolkit.
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

#ifndef QABSTRACTEVENTDISPATCHER_H
#define QABSTRACTEVENTDISPATCHER_H

#include "QtCore/qobject.h"
#include "QtCore/qeventloop.h"

class QAbstractEventDispatcherPrivate;
class QSocketNotifier;
template <typename T1, typename T2> struct QPair;

class Q_CORE_EXPORT QAbstractEventDispatcher : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QAbstractEventDispatcher)

public:
    typedef QPair<int, int> TimerInfo;

    explicit QAbstractEventDispatcher(QObject *parent = 0);
    ~QAbstractEventDispatcher();

    static QAbstractEventDispatcher *instance(QThread *thread = 0);

    virtual bool processEvents(QEventLoop::ProcessEventsFlags flags) = 0;
    virtual bool hasPendingEvents() = 0;

    virtual void registerSocketNotifier(QSocketNotifier *notifier) = 0;
    virtual void unregisterSocketNotifier(QSocketNotifier *notifier) = 0;

    int registerTimer(int interval, QObject *object);
    virtual void registerTimer(int timerId, int interval, QObject *object) = 0;
    virtual bool unregisterTimer(int timerId) = 0;
    virtual bool unregisterTimers(QObject *object) = 0;
    virtual QList<TimerInfo> registeredTimers(QObject *object) const = 0;

    virtual void wakeUp() = 0;
    virtual void interrupt() = 0;
    virtual void flush() = 0;

    virtual void startingUp();
    virtual void closingDown();

    typedef bool(*EventFilter)(void *message);
    EventFilter setEventFilter(EventFilter filter);
    bool filterEvent(void *message);

signals:
    void aboutToBlock();
    void awake();

protected:
    QAbstractEventDispatcher(QAbstractEventDispatcherPrivate &,
                             QObject *parent);
};

#endif // QABSTRACTEVENTDISPATCHER_H
