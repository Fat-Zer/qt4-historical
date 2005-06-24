/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#ifndef ABSTRACTFORMWINDOWCURSOR_H
#define ABSTRACTFORMWINDOWCURSOR_H

#include <QtDesigner/sdk_global.h>

class QDesignerFormWindowInterface;
class QWidget;
class QVariant;
class QString;

class QT_SDK_EXPORT QDesignerFormWindowCursorInterface
{
public:
    enum MoveOperation
    {
        NoMove,

        Start,
        End,
        Next,
        Prev,
        Left,
        Right,
        Up,
        Down
    };

    enum MoveMode
    {
        MoveAnchor,
        KeepAnchor
    };

public:
    virtual ~QDesignerFormWindowCursorInterface() {}

    virtual QDesignerFormWindowInterface *formWindow() const = 0;

    virtual bool movePosition(MoveOperation op, MoveMode mode = MoveAnchor) = 0;

    virtual int position() const = 0;
    virtual void setPosition(int pos, MoveMode mode = MoveAnchor) = 0;

    virtual QWidget *current() const = 0;

    virtual int widgetCount() const = 0;
    virtual QWidget *widget(int index) const = 0;

    virtual bool hasSelection() const = 0;
    virtual int selectedWidgetCount() const = 0;
    virtual QWidget *selectedWidget(int index) const = 0;

    virtual void setProperty(const QString &name, const QVariant &value) = 0;
    virtual void setWidgetProperty(QWidget *widget, const QString &name, const QVariant &value) = 0;
    virtual void resetWidgetProperty(QWidget *widget, const QString &name) = 0;

    bool isWidgetSelected(QWidget *widget) const;
};

#endif // ABSTRACTFORMWINDOWCURSOR_H
