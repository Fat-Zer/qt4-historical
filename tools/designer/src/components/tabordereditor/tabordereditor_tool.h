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

#ifndef TABORDEREDITOR_TOOL_H
#define TABORDEREDITOR_TOOL_H

#include "tabordereditor_global.h"

#include <QtCore/QPointer>

#include <QtDesigner/QtDesigner>

class QDesignerFormEditorInterface;
class QDesignerFormWindowInterface;
class QAction;

namespace qdesigner_internal {

class TabOrderEditor;

class QT_TABORDEREDITOR_EXPORT TabOrderEditorTool: public QDesignerFormWindowToolInterface
{
    Q_OBJECT
public:
    TabOrderEditorTool(QDesignerFormWindowInterface *formWindow, QObject *parent = 0);
    virtual ~TabOrderEditorTool();

    virtual QDesignerFormEditorInterface *core() const;
    virtual QDesignerFormWindowInterface *formWindow() const;

    virtual QWidget *editor() const;
    virtual QAction *action() const;

    virtual void activated();
    virtual void deactivated();

    virtual bool handleEvent(QWidget *widget, QWidget *managedWidget, QEvent *event);

private:
    QDesignerFormWindowInterface *m_formWindow;
    mutable QPointer<TabOrderEditor> m_editor;
    QAction *m_action;
};

}  // namespace qdesigner_internal

#endif // TABORDEREDITOR_TOOL_H
