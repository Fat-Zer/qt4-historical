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

#ifndef PALETTEEDITORBUTTON_H
#define PALETTEEDITORBUTTON_H

#include "propertyeditor_global.h"

#include <QtGui/QPalette>
#include <QtGui/QToolButton>

namespace qdesigner_internal {

class QT_PROPERTYEDITOR_EXPORT PaletteEditorButton: public QToolButton
{
    Q_OBJECT
public:
    PaletteEditorButton(const QPalette &palette, QWidget *parent = 0);
    virtual ~PaletteEditorButton();

    inline QPalette palette() const
    { return m_palette; }

signals:
    void changed();

public slots:
    void setPalette(const QPalette &palette);

private slots:
    void showPaletteEditor();

private:
    QPalette m_palette;
};

}  // namespace qdesigner_internal

#endif // PALETTEEDITORBUTTON_H
