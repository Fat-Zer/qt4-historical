/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the dialog module of the Qt Toolkit.
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

#ifndef QINPUTDIALOG_H
#define QINPUTDIALOG_H

#include "QtGui/qdialog.h"
#include "QtCore/qstring.h"
#include "QtGui/qlineedit.h"

#ifndef QT_NO_INPUTDIALOG

class QSpinBox;
class QComboBox;
class QInputDialogPrivate;

class Q_GUI_EXPORT QInputDialog : public QDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QInputDialog)

private:
    enum Type { LineEdit, SpinBox, DoubleSpinBox, ComboBox, EditableComboBox };

    QInputDialog(const QString &label, QWidget* parent, Type type, Qt::WFlags f);
    ~QInputDialog();

public:
    static QString getText(QWidget *parent, const QString &title, const QString &label,
                           QLineEdit::EchoMode echo = QLineEdit::Normal,
                           const QString &text = QString(), bool *ok = 0, Qt::WFlags f = 0);
    static int getInteger(QWidget *parent, const QString &title, const QString &label, int value = 0,
                          int minValue = -2147483647, int maxValue = 2147483647,
                          int step = 1, bool *ok = 0, Qt::WFlags f = 0);
    static double getDouble(QWidget *parent, const QString &title, const QString &label, double value = 0,
                            double minValue = -2147483647, double maxValue = 2147483647,
                            int decimals = 1, bool *ok = 0, Qt::WFlags f = 0);
    static QString getItem(QWidget *parent, const QString &title, const QString &label, const QStringList &list,
                           int current = 0, bool editable = true, bool *ok = 0,Qt::WFlags f = 0);

#ifdef QT3_SUPPORT
    inline static QT3_SUPPORT QString getText(const QString &title, const QString &label,
                                              QLineEdit::EchoMode echo = QLineEdit::Normal,
                                              const QString &text = QString(), bool *ok = 0,
                                              QWidget *parent = 0, const char * = 0, Qt::WFlags f = 0)
        { return getText(parent, title, label, echo, text, ok, f); }
    inline static QT3_SUPPORT int getInteger(const QString &title, const QString &label, int value = 0,
                                             int minValue = -2147483647, int maxValue = 2147483647,
                                             int step = 1, bool *ok = 0,
                                             QWidget *parent = 0, const char * = 0, Qt::WFlags f = 0)
        { return getInteger(parent, title, label, value, minValue, maxValue, step, ok, f); }
    inline static QT3_SUPPORT double getDouble(const QString &title, const QString &label, double value = 0,
                                               double minValue = -2147483647, double maxValue = 2147483647,
                                               int decimals = 1, bool *ok = 0,
                                               QWidget *parent = 0, const char * = 0, Qt::WFlags f = 0)
        { return getDouble(parent, title, label, value, minValue, maxValue, decimals, ok, f); }
    inline static QT3_SUPPORT QString getItem(const QString &title, const QString &label, const QStringList &list,
                                              int current = 0, bool editable = true, bool *ok = 0,
                                              QWidget *parent = 0, const char * = 0, Qt::WFlags f = 0)
        { return getItem(parent, title, label, list, current, editable, ok, f); }
#endif

private:
    Q_DISABLE_COPY(QInputDialog)
};

#endif // QT_NO_INPUTDIALOG

#endif // QINPUTDIALOG_H
