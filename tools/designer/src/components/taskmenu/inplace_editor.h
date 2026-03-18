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

#ifndef INPLACE_EDITOR_H
#define INPLACE_EDITOR_H

#include <QtGui/QLineEdit>

class QDesignerFormWindowInterface;

namespace qdesigner_internal {

class InPlaceEditor: public QLineEdit
{
    Q_OBJECT
public:
    InPlaceEditor(QWidget *widget, QDesignerFormWindowInterface *fw);
    virtual ~InPlaceEditor();

    virtual bool eventFilter(QObject *object, QEvent *event);

private:
    QWidget *m_widget;
    bool m_noChildEvent;
};

}  // namespace qdesigner_internal

#endif // INPLACE_EDITOR_H
