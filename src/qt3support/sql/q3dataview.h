/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt3Support module of the Qt Toolkit.
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

#ifndef Q3DATAVIEW_H
#define Q3DATAVIEW_H

#include "QtGui/qwidget.h"

QT_MODULE(Qt3Support)

#ifndef QT_NO_SQL_VIEW_WIDGETS

class Q3SqlForm;
class QSqlRecord;
class Q3DataViewPrivate;

class Q_COMPAT_EXPORT Q3DataView : public QWidget
{
    Q_OBJECT

public:
    Q3DataView(QWidget* parent=0, const char* name=0, Qt::WFlags fl = 0);
    ~Q3DataView();

    virtual void setForm(Q3SqlForm* form);
    Q3SqlForm* form();
    virtual void setRecord(QSqlRecord* record);
    QSqlRecord* record();

public slots:
    virtual void refresh(QSqlRecord* buf);
    virtual void readFields();
    virtual void writeFields();
    virtual void clearValues();

private:
    Q_DISABLE_COPY(Q3DataView)

    Q3DataViewPrivate* d;
};

#endif
#endif
