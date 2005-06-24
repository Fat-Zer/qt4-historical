/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the gui module of the Qt Toolkit.
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

#ifndef QSHORTCUT_H
#define QSHORTCUT_H

#include "QtCore/qobject.h"
#include "QtGui/qwidget.h"
#include "QtGui/qkeysequence.h"

class QShortcutPrivate;
class Q_GUI_EXPORT QShortcut : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QShortcut)
    Q_PROPERTY(QKeySequence key READ key WRITE setKey)
    Q_PROPERTY(QString whatsThis READ whatsThis WRITE setWhatsThis)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(Qt::ShortcutContext context READ context WRITE setContext)
public:
    explicit QShortcut(QWidget *parent);
    QShortcut(const QKeySequence& key, QWidget *parent,
              const char *member = 0, const char *ambiguousMember = 0,
              Qt::ShortcutContext context = Qt::WindowShortcut);
    ~QShortcut();

    void setKey(const QKeySequence& key);
    QKeySequence key() const;

    void setEnabled(bool enable);
    bool isEnabled() const;

    void setContext(Qt::ShortcutContext context);
    Qt::ShortcutContext context();

    void setWhatsThis(const QString &text);
    QString whatsThis() const;

    int id() const;

    inline QWidget *parentWidget() const
    { return static_cast<QWidget *>(QObject::parent()); }

signals:
    void activated();
    void activatedAmbiguously();

protected:
    bool event(QEvent *e);
};

#endif // QSHORTCUT_H
