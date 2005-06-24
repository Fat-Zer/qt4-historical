/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the gui module of the Qt Toolkit.
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

#ifndef QACTION_P_H
#define QACTION_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qaction.h"
#include <private/qobject_p.h>
#include "qmenu.h"

#ifdef QT3_SUPPORT
class QMenuItemEmitter;
#endif

class QShortcutMap;

class QActionPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QAction)
public:
    QActionPrivate();
    ~QActionPrivate();

    QPointer<QActionGroup> group;
    QString text;
    QString iconText;
    QIcon icon;
    QString tooltip;
    QString statustip;
    QString whatsthis;
    QKeySequence shortcut;
    QVariant userData;
    int shortcutId;
    Qt::ShortcutContext shortcutContext;
    QFont font;
    QPointer<QMenu> menu;
    uint enabled : 1, forceDisabled : 1;
    uint visible : 1, forceInvisible : 1;
    uint checkable : 1;
    uint checked : 1;
    uint separator : 1;

    QList<QWidget *> widgets;

    void redoGrab(QShortcutMap &map);
    void setShortcutEnabled(bool enable, QShortcutMap &map);

    static QShortcutMap *globalMap;

#ifdef QT3_SUPPORT //for menubar/menu compat
    QMenuItemEmitter *act_signal;
    int id, param;
#endif
    void sendDataChanged();
};

#endif // QACTION_P_H
