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

#include "formwindowsettings.h"
#include <QtDesigner/QtDesigner>
#include <QtGui/QStyle>

FormWindowSettings::FormWindowSettings(QDesignerFormWindowInterface *parent)
    : QDialog(parent), m_formWindow(parent)
{
    ui.setupUi(this);

    int defaultMargin = INT_MIN, defaultSpacing = INT_MIN;
    formWindow()->layoutDefault(&defaultMargin, &defaultSpacing);

    QStyle *style = formWindow()->style();
    ui.defaultMarginSpinBox->setValue(style->pixelMetric(QStyle::PM_DefaultTopLevelMargin, 0));
    ui.defaultSpacingSpinBox->setValue(style->pixelMetric(QStyle::PM_DefaultLayoutSpacing, 0));

    if (defaultMargin != INT_MIN || defaultMargin != INT_MIN) {
        ui.layoutDefaultGroupBox->setChecked(true);

        if (defaultMargin != INT_MIN)
            ui.defaultMarginSpinBox->setValue(defaultMargin);

        if (defaultSpacing != INT_MIN)
            ui.defaultSpacingSpinBox->setValue(defaultSpacing);
    } else {
        ui.layoutDefaultGroupBox->setChecked(false);
    }

    QString marginFunction, spacingFunction;
    formWindow()->layoutFunction(&marginFunction, &spacingFunction);
    if (!marginFunction.isEmpty() || !spacingFunction.isEmpty()) {
        ui.layoutFunctionGroupBox->setChecked(true);
        ui.marginFunctionLineEdit->setText(marginFunction);
        ui.spacingFunctionLineEdit->setText(spacingFunction);
    } else {
        ui.layoutFunctionGroupBox->setChecked(false);
    }

    QString pixFunction = formWindow()->pixmapFunction();
    ui.pixmapFunctionGroupBox->setChecked(!pixFunction.isEmpty());
    ui.pixmapFunctionLineEdit->setText(pixFunction);

    ui.authorLineEdit->setText(formWindow()->author());

    foreach (QString includeHint, formWindow()->includeHints()) {
        if (includeHint.isEmpty())
            continue;

        ui.includeHintsTextEdit->append(includeHint);
    }
}

FormWindowSettings::~FormWindowSettings()
{
}

QDesignerFormWindowInterface *FormWindowSettings::formWindow() const
{
    return m_formWindow;
}

void FormWindowSettings::accept()
{
    formWindow()->setAuthor(ui.authorLineEdit->text());

    if (ui.pixmapFunctionGroupBox->isChecked())
        formWindow()->setPixmapFunction(ui.pixmapFunctionLineEdit->text());

    if (ui.layoutDefaultGroupBox->isChecked())
        formWindow()->setLayoutDefault(ui.defaultMarginSpinBox->value(), ui.defaultSpacingSpinBox->value());

    if (ui.layoutFunctionGroupBox->isChecked())
        formWindow()->setLayoutFunction(ui.marginFunctionLineEdit->text(), ui.spacingFunctionLineEdit->text());

    formWindow()->setIncludeHints(ui.includeHintsTextEdit->toPlainText().split(QLatin1String("\n")));

    QDialog::accept();
}
