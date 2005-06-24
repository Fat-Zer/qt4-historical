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

#ifndef PREVIEWFRAME_H
#define PREVIEWFRAME_H

#include <QtGui/QWorkspace>
#include <QtGui/QFrame>

namespace qdesigner_internal {

class PreviewWidget;

class PreviewWorkspace: public QWorkspace
{
    Q_OBJECT
public:
    PreviewWorkspace(QWidget *parent)
        : QWorkspace(parent) {}

    virtual ~PreviewWorkspace() {}

protected:
    void paintEvent(QPaintEvent *);
};

class PreviewFrame: public QFrame
{
    Q_OBJECT
public:
    PreviewFrame(QWidget *parent);

    void setPreviewPalette(const QPalette &palette);

private:
    PreviewWidget *previewWidget;
};

}  // namespace qdesigner_internal

#endif
