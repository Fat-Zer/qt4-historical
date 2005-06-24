/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#ifndef QPROPERTYEDITOR_H
#define QPROPERTYEDITOR_H

#include "propertyeditor_global.h"
#include "qpropertyeditor_items_p.h"

#include <QtGui/QTreeView>

namespace qdesigner_internal {

class QPropertyEditorModel;
class QPropertyEditorDelegate;

class QT_PROPERTYEDITOR_EXPORT QPropertyEditor: public QTreeView
{
    Q_OBJECT
public:
    QPropertyEditor(QWidget *parent = 0);
    ~QPropertyEditor();

    IProperty *initialInput() const;
    bool isReadOnly() const;

    inline QPropertyEditorModel *editorModel() const
    { return m_model; }

signals:
    void propertyChanged(IProperty *property);

public slots:
    void setInitialInput(IProperty *initialInput);
    void setReadOnly(bool readOnly);

protected:
    virtual void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
    virtual void keyPressEvent(QKeyEvent *ev);

private:
    QPropertyEditorModel *m_model;
    QPropertyEditorDelegate *m_itemDelegate;
};

}  // namespace qdesigner_internal

#endif // QPROPERTYEDITOR_H
