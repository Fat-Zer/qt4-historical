/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#include <QtNetwork>

#include "client.h"
#include "connection.h"
#include "peermanager.h"

Client::Client()
{
    peerManager = new PeerManager(this);
    peerManager->setServerPort(server.serverPort());
    peerManager->startBroadcasting();

    QObject::connect(peerManager, SIGNAL(newConnection(Connection *)),
                     this, SLOT(newConnection(Connection *)));
    QObject::connect(&server, SIGNAL(newConnection(Connection *)),
                     this, SLOT(newConnection(Connection *)));
}

void Client::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return;

    QList<Connection *> connections = peers.values();
    foreach (Connection *connection, connections)
        connection->sendMessage(message);
}

QString Client::nickName() const
{
    return QString(peerManager->userName()) + "@" + QHostInfo::localHostName()
           + ":" + QString::number(server.serverPort());
}

bool Client::hasConnection(const QHostAddress &senderIp, int senderPort) const
{
    if (senderPort == -1)
        return peers.contains(senderIp);

    if (!peers.contains(senderIp))
        return false;

    QList<Connection *> connections = peers.values(senderIp);
    foreach (Connection *connection, connections) {
        if (connection->peerPort() == senderPort)
            return true;
    }

    return false;
}

void Client::newConnection(Connection *connection)
{
    connection->setGreetingMessage(peerManager->userName());

    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(connectionError(QAbstractSocket::SocketError)));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(connection, SIGNAL(readyForUse()), this, SLOT(readyForUse()));
}

void Client::readyForUse()
{
    Connection *connection = qobject_cast<Connection *>(sender());
    if (!connection || hasConnection(connection->peerAddress(),
                                     connection->peerPort()))
        return;

    connect(connection, SIGNAL(newMessage(const QString &, const QString &)),
            this, SIGNAL(newMessage(const QString &, const QString &)));

    peers.insert(connection->peerAddress(), connection);
    QString nick = connection->name();
    if (!nick.isEmpty())
        emit newParticipant(nick);
}

void Client::disconnected()
{
    if (Connection *connection = qobject_cast<Connection *>(sender()))
        removeConnection(connection);
}

void Client::connectionError(QAbstractSocket::SocketError /* socketError */)
{
    if (Connection *connection = qobject_cast<Connection *>(sender()))
        removeConnection(connection);
}

void Client::removeConnection(Connection *connection)
{
    if (peers.contains(connection->peerAddress())) {
        peers.remove(connection->peerAddress());
        QString nick = connection->name();
        if (!nick.isEmpty())
            emit participantLeft(nick);
    }
    connection->deleteLater();
}
