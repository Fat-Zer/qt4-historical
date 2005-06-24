/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the linguist application of the Qt Toolkit.
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

#include "statistics.h"

#include <qvariant.h>
#include <qimage.h>
#include <qpixmap.h>

Statistics::Statistics(QWidget* parent, Qt::WFlags fl)
: QDialog(parent, fl)
{
    setupUi(this);
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void Statistics::languageChange()
{
    retranslateUi(this);
}

void Statistics::updateStats(int sW,int sC,int sCS,int trW,int trC,int trCS)
{
    untrWords->setText(QString::number(sW));
    untrChars->setText(QString::number(sC)); 
    untrCharsSpc->setText(QString::number(sCS));
    trWords->setText(QString::number(trW));
    trChars->setText(QString::number(trC));
    trCharsSpc->setText(QString::number(trCS));
}
