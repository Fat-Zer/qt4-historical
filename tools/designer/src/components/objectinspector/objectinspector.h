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

#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include "objectinspector_global.h"
#include <QtDesigner/QtDesigner>
#include <QtCore/QPointer>

class QDesignerFormEditorInterface;
class QDesignerFormWindowInterface;
class TreeWidget;

namespace qdesigner_internal {

class ObjectItem;

class QT_OBJECTINSPECTOR_EXPORT ObjectInspector: public QDesignerObjectInspectorInterface
{
    Q_OBJECT
public:
    ObjectInspector(QDesignerFormEditorInterface *core, QWidget *parent = 0);
    virtual ~ObjectInspector();

    virtual QDesignerFormEditorInterface *core() const;

    void setFormWindow(QDesignerFormWindowInterface *formWindow);

private slots:
    void slotSelectionChanged();

protected:
    virtual void showEvent(QShowEvent *enent);

private:
    static bool sortEntry(const QObject *a, const QObject *b);

private:
    QDesignerFormEditorInterface *m_core;
    TreeWidget *m_treeWidget;
    QPointer<QDesignerFormWindowInterface> m_formWindow;
    ObjectItem *m_root;
    QPointer<QObject> m_selected;
    bool m_ignoreNextUpdate;
};

}  // namespace qdesigner_internal

#endif // OBJECTINSPECTOR_H
