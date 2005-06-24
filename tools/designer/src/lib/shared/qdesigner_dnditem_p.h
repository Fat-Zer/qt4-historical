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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef QDESIGNER_DNDITEM_H
#define QDESIGNER_DNDITEM_H

#include <QtCore/QPoint>

#include "shared_global_p.h"
#include <QtDesigner/abstractdnditem.h>

class QT_SHARED_EXPORT QDesignerDnDItem: public QDesignerDnDItemInterface
{
public:
    QDesignerDnDItem(DropType type, QWidget *source = 0);
    virtual ~QDesignerDnDItem();

    virtual DomUI *domUi() const;
    virtual QWidget *decoration() const;
    virtual QWidget *widget() const;
    virtual QPoint hotSpot() const;
    virtual QWidget *source() const;

    virtual DropType type() const;

protected:
    void setDomUi(DomUI *dom_ui);
    virtual void init(DomUI *ui, QWidget *widget, QWidget *decoration, const QPoint &global_mouse_pos);

private:
    QWidget *m_source;
    DropType m_type;
    DomUI *m_dom_ui;
    QWidget *m_widget;
    QWidget *m_decoration;
    QPoint m_hot_spot;

    Q_DISABLE_COPY(QDesignerDnDItem)
};
#endif // QDESIGNER_DNDITEM_H
