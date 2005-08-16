/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#ifndef SENDER_H
#define SENDER_H

#include <QDialog>

class QLabel;
class QPushButton;
class QTimer;
class QUdpSocket;

class Sender : public QDialog
{
    Q_OBJECT

public:
    Sender(QWidget *parent = 0);

private slots:
    void startBroadcasting();
    void broadcastDatagram();

private:
    QLabel *statusLabel;
    QPushButton *startButton;
    QPushButton *quitButton;
    QUdpSocket *udpSocket;
    QTimer *timer;
    int messageNo;
};

#endif
