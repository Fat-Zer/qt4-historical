/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QGROUPBOX_H
#define QGROUPBOX_H

#include "QtGui/qframe.h"

#ifndef QT_NO_GROUPBOX

class QGroupBoxPrivate;
class Q_GUI_EXPORT QGroupBox : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(bool flat READ isFlat WRITE setFlat)
    Q_PROPERTY(bool checkable READ isCheckable WRITE setCheckable)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
public:
    explicit QGroupBox(QWidget* parent=0);
    explicit QGroupBox(const QString &title, QWidget* parent=0);
    ~QGroupBox();

    QString title() const;
    void setTitle(const QString &);

    Qt::Alignment alignment() const;
    void setAlignment(int);

    QSize minimumSizeHint() const;

    bool isFlat() const;
    void setFlat(bool b);
    bool isCheckable() const;
    void setCheckable(bool b);
    bool isChecked() const;

public slots:
    void setChecked(bool b);

signals:
    void toggled(bool);

protected:
    bool event(QEvent *);
    void childEvent(QChildEvent *);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void focusInEvent(QFocusEvent *);
    void changeEvent(QEvent *);

#ifdef QT3_SUPPORT
public:
    QT3_SUPPORT_CONSTRUCTOR QGroupBox(QWidget* parent, const char* name);
    QT3_SUPPORT_CONSTRUCTOR QGroupBox(const QString &title, QWidget* parent, const char* name);
#endif

private:
    Q_DISABLE_COPY(QGroupBox)
    Q_DECLARE_PRIVATE(QGroupBox)
    Q_PRIVATE_SLOT(d_func(), void fixFocus())
    Q_PRIVATE_SLOT(d_func(), void setChildrenEnabled(bool b))
};

#endif // QT_NO_GROUPBOX

#endif // QGROUPBOX_H
