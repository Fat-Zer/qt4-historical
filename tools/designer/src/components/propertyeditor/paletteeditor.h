/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef PALETTEEDITOR_H
#define PALETTEEDITOR_H

#include "ui_paletteeditor.h"

namespace qdesigner_internal {

class PaletteEditor: public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QPalette editPalette READ editPalette WRITE setEditPalette)
public:
    virtual ~PaletteEditor();

    static QPalette getPalette(QWidget* parent, const QPalette &init = QPalette(), int *result = 0);

    QPalette editPalette() const;
    void setEditPalette(const QPalette&);

private slots:
    void on_buttonMainColor_clicked();
    void on_buttonMainColor2_clicked();
    void on_btnAdvanced_clicked();
    void on_paletteCombo_activated(int);

protected:
    PaletteEditor(QWidget *parent);

private:
    void buildPalette();

    void buildActiveEffect();
    void updatePaletteEffect(QPalette::ColorGroup g);

    void updatePreviewPalette();
    void updateStyledButtons();

    QPalette::ColorGroup selectedColorGroup() const;

private:
    Ui::PaletteEditor ui;
    QPalette m_editPalette;
};

}  // namespace qdesigner_internal

#endif // PALETTEEDITOR_H
