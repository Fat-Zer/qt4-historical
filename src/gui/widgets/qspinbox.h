/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QSPINBOX_H
#define QSPINBOX_H

#include <QtGui/qabstractspinbox.h>

class QSpinBoxPrivate;
class Q_GUI_EXPORT QSpinBox : public QAbstractSpinBox
{
    Q_OBJECT

    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString cleanText READ cleanText)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit QSpinBox(QWidget *parent = 0);
#ifdef QT_COMPAT
    QT_COMPAT_CONSTRUCTOR QSpinBox(QWidget *parent, const char *name);
    QT_COMPAT_CONSTRUCTOR QSpinBox(int min, int max, int step, QWidget *parent,
                                   const char *name = 0);
#endif

    int value() const;

    QString prefix() const;
    void setPrefix(const QString &p);

    QString suffix() const;
    void setSuffix(const QString &s);

    QString cleanText() const;

    int singleStep() const;
    void setSingleStep(int val);

    int minimum() const;
    void setMinimum(int min);

    int maximum() const;
    void setMaximum(int max);

    void setRange(int min, int max);

#ifdef QT_COMPAT
    inline QT_COMPAT void setLineStep(int step) { setSingleStep(step); }
    inline QT_COMPAT void setMaxValue(int val) { setMaximum(val); }
    inline QT_COMPAT void setMinValue(int val) { setMinimum(val); }
    inline QT_COMPAT int maxValue() const { return maximum(); }
    inline QT_COMPAT int minValue() const { return minimum(); }
#endif

protected:
    virtual QValidator::State validate(QString &input, int &pos) const;
    virtual int valueFromText(const QString &text) const;
    virtual QString textFromValue(int v) const;
    virtual void fixup(QString &str) const;


public slots:
    void setValue(int val);

signals:
    void valueChanged(int);
    void valueChanged(const QString &);

private:
    Q_DISABLE_COPY(QSpinBox)
    Q_DECLARE_PRIVATE(QSpinBox)
};

class QDoubleSpinBoxPrivate;
class Q_GUI_EXPORT QDoubleSpinBox : public QAbstractSpinBox
{
    Q_OBJECT

    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(QString cleanText READ cleanText)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit QDoubleSpinBox(QWidget *parent = 0);

    double value() const;

    QString prefix() const;
    void setPrefix(const QString &p);

    QString suffix() const;
    void setSuffix(const QString &s);

    QString cleanText() const;

    double singleStep() const;
    void setSingleStep(double val);

    double minimum() const;
    void setMinimum(double min);

    double maximum() const;
    void setMaximum(double max);

    void setRange(double min, double max);

    int decimals() const;
    void setDecimals(int prec);

    virtual QValidator::State validate(QString &input, int &pos) const;
    virtual double valueFromText(const QString &text) const;
    virtual QString textFromValue(double v) const;
    virtual void fixup(QString &str) const;

public slots:
    void setValue(double val);

signals:
    void valueChanged(double);
    void valueChanged(const QString &);

private:
    Q_DISABLE_COPY(QDoubleSpinBox)
    Q_DECLARE_PRIVATE(QDoubleSpinBox)
};

#endif // QSPINBOX_H
