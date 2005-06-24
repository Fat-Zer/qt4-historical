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

#ifndef FLAGBOX_P_H
#define FLAGBOX_P_H

#include "propertyeditor_global.h"
#include "flagbox_model_p.h"

#include <QtGui/QComboBox>

namespace qdesigner_internal {

class QT_PROPERTYEDITOR_EXPORT FlagBox: public QComboBox
{
    Q_OBJECT
public:
    FlagBox(QWidget *parent = 0);
    virtual ~FlagBox();

    inline FlagBoxModelItem itemAt(int index) const
    { return m_model->itemAt(index); }

    inline FlagBoxModelItem &item(int index)
    { return m_model->item(index); }

    inline QList<FlagBoxModelItem> items() const
    { return m_model->items(); }

    inline void setItems(const QList<FlagBoxModelItem> &items)
    { m_model->setItems(items); }

    inline void hidePopup() {}

private slots:
    void slotActivated(int index);

private:
    FlagBoxModel *m_model;
};

}  // namespace qdesigner_internal

#endif // FLAGBOX_P_H
