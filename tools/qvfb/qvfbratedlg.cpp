/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the virtual framebuffer of the Qt Toolkit.
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

#include "qvfbratedlg.h"

#include <qlayout.h>
#include <qlabel.h>
#include <qslider.h>
#include <qpushbutton.h>

QVFbRateDialog::QVFbRateDialog(int rate, QWidget *parent)
    : QDialog(parent)
{
    oldRate = rate;

    QVBoxLayout *tl = new QVBoxLayout(this);
    tl->setMargin(5);

    QLabel *label = new QLabel( "Target frame rate:", this );
    tl->addWidget( label );

    QHBoxLayout *hl = new QHBoxLayout( tl );
    rateSlider = new QSlider(Qt::Horizontal, this);
    rateSlider->setRange(1,100);
    rateSlider->setPageStep(10);
    rateSlider->setValue(rate);

    hl->addWidget( rateSlider );
    connect( rateSlider, SIGNAL(valueChanged(int)), this, SLOT(rateChanged(int)) );
    rateLabel = new QLabel( QString( "%1fps" ).arg(rate), this );
    hl->addWidget( rateLabel );

    hl = new QHBoxLayout( tl );
    QPushButton *pb = new QPushButton( "OK", this );
    connect( pb, SIGNAL(clicked()), this, SLOT(accept()) );
    hl->addWidget( pb );
    pb = new QPushButton( "Cancel", this );
    connect( pb, SIGNAL(clicked()), this, SLOT(cancel()) );
    hl->addWidget( pb );
}

void QVFbRateDialog::rateChanged( int r )
{
    if ( rateSlider->value() != r )
	rateSlider->setValue( r );
    rateLabel->setText( QString( "%1fps" ).arg(r) );
    emit updateRate(r);
}

void QVFbRateDialog::cancel()
{
    rateChanged( oldRate );
    reject();
}
