/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

#ifndef SIGNALSLOTEDITOR_TOOL_H
#define SIGNALSLOTEDITOR_TOOL_H

#include "signalsloteditor_global.h"
#include "signalsloteditor.h"

#include <QtCore/QPointer>

#include <QtDesigner/QtDesigner>

class QDesignerFormEditorInterface;
class QDesignerFormWindowInterface;
class SignalSlotEditor;
class QAction;

class QT_SIGNALSLOTEDITOR_EXPORT SignalSlotEditorTool: public QDesignerFormWindowToolInterface
{
    Q_OBJECT
public:
    SignalSlotEditorTool(QDesignerFormWindowInterface *formWindow, QObject *parent = 0);
    virtual ~SignalSlotEditorTool();

    virtual QDesignerFormEditorInterface *core() const;
    virtual QDesignerFormWindowInterface *formWindow() const;

    virtual QWidget *editor() const;

    QAction *action() const;

    virtual void activated();
    virtual void deactivated();

    virtual bool handleEvent(QWidget *widget, QWidget *managedWidget, QEvent *event);

    virtual void saveToDom(DomUI *ui, QWidget *mainContainer);
    virtual void loadFromDom(DomUI *ui, QWidget *mainContainer);

private:
    QDesignerFormWindowInterface *m_formWindow;
    mutable QPointer<qdesigner_internal::SignalSlotEditor> m_editor;
    QAction *m_action;
};

#endif // SIGNALSLOTEDITOR_TOOL_H
