/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtNetwork module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. 
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "qlocalsocket.h"
#include "qlocalsocket_p.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <qdatetime.h>
#include <qdir.h>
#include <qdebug.h>

#define QT_CONNECT_TIMEOUT 30000

QT_BEGIN_NAMESPACE

QLocalSocketPrivate::QLocalSocketPrivate() : QIODevicePrivate(),
        delayConnect(0),
        connectTimer(0),
        connectingSocket(-1),
        connectingOpenMode(0),
        state(QLocalSocket::UnconnectedState)
{
}

void QLocalSocketPrivate::init()
{
    Q_Q(QLocalSocket);
    // QIODevice signals
    q->connect(&unixSocket, SIGNAL(aboutToClose()), q, SIGNAL(aboutToClose()));
    q->connect(&unixSocket, SIGNAL(bytesWritten(qint64)),
               q, SIGNAL(bytesWritten(qint64)));
    q->connect(&unixSocket, SIGNAL(readyRead()), q, SIGNAL(readyRead()));
    // QAbstractSocket signals
    q->connect(&unixSocket, SIGNAL(connected()), q, SIGNAL(connected()));
    q->connect(&unixSocket, SIGNAL(disconnected()), q, SIGNAL(disconnected()));
    q->connect(&unixSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
               q, SLOT(_q_stateChanged(QAbstractSocket::SocketState)));
    q->connect(&unixSocket, SIGNAL(error(QAbstractSocket::SocketError)),
               q, SLOT(_q_error(QAbstractSocket::SocketError)));
    q->connect(&unixSocket, SIGNAL(readChannelFinished()), q, SIGNAL(readChannelFinished()));
    unixSocket.setParent(q);
}

void QLocalSocketPrivate::_q_error(QAbstractSocket::SocketError socketError)
{
    Q_Q(QLocalSocket);
    QString function = QLatin1String("QLocalSocket");
    QLocalSocket::LocalSocketError error = (QLocalSocket::LocalSocketError)socketError;
    QString errorString = generateErrorString(error, function);
    q->setErrorString(errorString);
    emit q->error(error);
}

void QLocalSocketPrivate::_q_stateChanged(QAbstractSocket::SocketState newState)
{
    Q_Q(QLocalSocket);
    QLocalSocket::LocalSocketState currentState = state;
    switch(newState) {
    case QAbstractSocket::UnconnectedState:
        state = QLocalSocket::UnconnectedState;
        serverName = QString();
        fullServerName = QString();
        break;
    case QAbstractSocket::ConnectingState:
        state = QLocalSocket::ConnectingState;
        break;
    case QAbstractSocket::ConnectedState:
        state = QLocalSocket::ConnectedState;
        break;
    case QAbstractSocket::ClosingState:
        state = QLocalSocket::ClosingState;
        break;
    default:
#if defined QLOCALSOCKET_DEBUG
        qWarning() << "QLocalSocket::Unhandled socket state change:" << newState;
#endif
        return;
    }
    if (currentState != state)
        emit q->stateChanged(state);
}

QString QLocalSocketPrivate::generateErrorString(QLocalSocket::LocalSocketError error, const QString &function) const
{
    QString errorString;
    switch (error) {
    case QLocalSocket::ConnectionRefusedError:
        errorString = QLocalSocket::tr("%1: Connection refused").arg(function);
        break;
    case QLocalSocket::PeerClosedError:
        errorString = QLocalSocket::tr("%1: Remote closed").arg(function);
        break;
    case QLocalSocket::ServerNotFoundError:
        errorString = QLocalSocket::tr("%1: Invalid name").arg(function);
        break;
    case QLocalSocket::SocketAccessError:
        errorString = QLocalSocket::tr("%1: Socket access error").arg(function);
        break;
    case QLocalSocket::SocketResourceError:
        errorString = QLocalSocket::tr("%1: Socket resource error").arg(function);
        break;
    case QLocalSocket::SocketTimeoutError:
        errorString = QLocalSocket::tr("%1: Socket operation timed out").arg(function);
        break;
    case QLocalSocket::DatagramTooLargeError:
        errorString = QLocalSocket::tr("%1: Datagram too large").arg(function);
        break;
    case QLocalSocket::ConnectionError:
        errorString = QLocalSocket::tr("%1: Connection error").arg(function);
        break;
    case QLocalSocket::UnsupportedSocketOperationError:
        errorString = QLocalSocket::tr("%1: The socket operation is not supported").arg(function);
        break;
    case QLocalSocket::UnknownSocketError:
    default:
        errorString = QLocalSocket::tr("%1: Unknown error %2").arg(function).arg(errno);
    }
    return errorString;
}

void QLocalSocketPrivate::errorOccurred(QLocalSocket::LocalSocketError error, const QString &function)
{
    Q_Q(QLocalSocket);
    switch (error) {
    case QLocalSocket::ConnectionRefusedError:
        unixSocket.setSocketError(QAbstractSocket::ConnectionRefusedError);
        break;
    case QLocalSocket::PeerClosedError:
        unixSocket.setSocketError(QAbstractSocket::RemoteHostClosedError);
        break;
    case QLocalSocket::ServerNotFoundError:
        unixSocket.setSocketError(QAbstractSocket::HostNotFoundError);
        break;
    case QLocalSocket::SocketAccessError:
        unixSocket.setSocketError(QAbstractSocket::SocketAccessError);
        break;
    case QLocalSocket::SocketResourceError:
        unixSocket.setSocketError(QAbstractSocket::SocketResourceError);
        break;
    case QLocalSocket::SocketTimeoutError:
        unixSocket.setSocketError(QAbstractSocket::SocketTimeoutError);
        break;
    case QLocalSocket::DatagramTooLargeError:
        unixSocket.setSocketError(QAbstractSocket::DatagramTooLargeError);
        break;
    case QLocalSocket::ConnectionError:
        unixSocket.setSocketError(QAbstractSocket::NetworkError);
        break;
    case QLocalSocket::UnsupportedSocketOperationError:
        unixSocket.setSocketError(QAbstractSocket::UnsupportedSocketOperationError);
        break;
    case QLocalSocket::UnknownSocketError:
    default:
        unixSocket.setSocketError(QAbstractSocket::UnknownSocketError);
    }

    QString errorString = generateErrorString(error, function);
    q->setErrorString(errorString);
    emit q->error(error);

    // errors cause a disconnect
    unixSocket.setSocketState(QAbstractSocket::UnconnectedState);
    bool stateChanged = (state != QLocalSocket::UnconnectedState);
    state = QLocalSocket::UnconnectedState;
    q->close();
    if (stateChanged)
        q->emit stateChanged(state);
}

/*!
    Attempts to make a connection to \a name.

    The socket is opened in the given \a openMode and first enters ConnectingState.
    It then attempts to connect to the address or addresses returned by the lookup.
    Finally, if a connection is established, QLocalSocket enters ConnectedState
    and emits connected().

    At any point, the socket can emit error() to signal that an error occurred.

    See also state(), serverName(), and waitForConnected().
  */
void QLocalSocket::connectToServer(const QString &name, OpenMode openMode)
{
    Q_D(QLocalSocket);
    if (state() == ConnectedState
        || state() == ConnectingState)
        return;

    d->errorString = QString();
    d->unixSocket.setSocketState(QAbstractSocket::ConnectingState);
    d->state = ConnectingState;
    emit stateChanged(d->state);

    if (name.isEmpty()) {
        d->errorOccurred(ServerNotFoundError,
                QLatin1String("QLocalSocket::connectToServer"));
        return;
    }

    // create the socket
    if (-1 == (d->connectingSocket = qSocket(PF_UNIX, SOCK_STREAM, 0))) {
        d->errorOccurred(UnsupportedSocketOperationError,
                        QLatin1String("QLocalSocket::connectToServer"));
        return;
    }

    // set non blocking so we can try to connect and it wont wait
    int flags = fcntl(d->connectingSocket, F_GETFL, 0);
    if (-1 == flags
        || -1 == (fcntl(d->connectingSocket, F_SETFL, flags | O_NONBLOCK))) {
        d->errorOccurred(UnknownSocketError,
                QLatin1String("QLocalSocket::connectToServer"));
        return;
    }

    // _q_connectToSocket does the actual connecting
    d->connectingName = name;
    d->connectingOpenMode = openMode;
    d->_q_connectToSocket();
}

/*!
    \internal

    Tries to connect connectingName and connectingOpenMode

    \sa connectToServer() waitForConnected()
  */
void QLocalSocketPrivate::_q_connectToSocket()
{
    Q_Q(QLocalSocket);
    QString connectingPathName;

    // determine the full server path
    if (connectingName.startsWith(QLatin1Char('/'))) {
        connectingPathName = connectingName;
    } else {
        connectingPathName = QDir::tempPath();
        connectingPathName += QLatin1Char('/') + connectingName;
    }

    struct sockaddr_un name;
    name.sun_family = PF_UNIX;
    if (sizeof(sockaddr_un) < (uint)connectingPathName.toLatin1().size()) {
        QString function = QLatin1String("QLocalSocket::connectToServer");
        errorOccurred(QLocalSocket::ServerNotFoundError, function);
        return;
    }
    ::memcpy(name.sun_path, connectingPathName.toLatin1().data(),
             connectingPathName.toLatin1().size() + 1);
    if (-1 == qConnect(connectingSocket, (struct sockaddr *)&name, sizeof(name))) {
        QString function = QLatin1String("QLocalSocket::connectToServer");
        switch (errno)
        {
        case EINVAL:
        case ECONNREFUSED:
            errorOccurred(QLocalSocket::ConnectionRefusedError, function);
            break;
        case ENOENT:
            errorOccurred(QLocalSocket::ServerNotFoundError, function);
            break;
        case EACCES:
        case EPERM:
            errorOccurred(QLocalSocket::SocketAccessError, function);
            break;
        case ETIMEDOUT:
            errorOccurred(QLocalSocket::SocketTimeoutError, function);
            break;
        case EAGAIN:
            // Try again later, all of the sockets listening are full
            if (!delayConnect) {
                delayConnect = new QSocketNotifier(connectingSocket, QSocketNotifier::Write);
                q->connect(delayConnect, SIGNAL(activated(int)), q, SLOT(_q_connectToSocket()));
            }
            if (!connectTimer) {
                connectTimer = new QTimer(q);
                q->connect(connectTimer, SIGNAL(timeout()),
                                 q, SLOT(_q_abortConnectionAttempt()),
                                 Qt::DirectConnection);
                connectTimer->start(QT_CONNECT_TIMEOUT);
            }
            delayConnect->setEnabled(true);
            break;
        default:
            errorOccurred(QLocalSocket::UnknownSocketError, function);
        }
        return;
    }

    // connected!
    if (delayConnect) {
        delayConnect->setEnabled(false);
        delete delayConnect;
        delayConnect = 0;
    }
    serverName = connectingName;
    fullServerName = connectingPathName;
    if (unixSocket.setSocketDescriptor(connectingSocket,
        QAbstractSocket::ConnectedState, connectingOpenMode)) {
        q->setOpenMode(connectingOpenMode);
        q->emit connected();
    } else {
        QString function = QLatin1String("QLocalSocket::connectToServer");
        errorOccurred(QLocalSocket::UnknownSocketError, function);
    }
    connectingSocket = -1;
    connectingName = QString();
    connectingOpenMode = 0;
}

/*!
    Initializes QLocalSocket with the native socket descriptor
    \a socketDescriptor. Returns true if socketDescriptor is accepted
    as a valid socket descriptor; otherwise returns false. The socket is
    opened in the mode specified by \a openMode, and enters the socket state
    specified by \a socketState.

    Note: It is not possible to initialize two local sockets with the same
    native socket descriptor.

    \sa socketDescriptor(), state(), openMode()
 */
bool QLocalSocket::setSocketDescriptor(quintptr socketDescriptor,
        LocalSocketState socketState, OpenMode openMode)
{
    Q_D(QLocalSocket);
    QAbstractSocket::SocketState newSocketState = QAbstractSocket::UnconnectedState;
    switch (socketState) {
    case ConnectingState:
        newSocketState = QAbstractSocket::ConnectingState;
        break;
    case ConnectedState:
        newSocketState = QAbstractSocket::ConnectedState;
        break;
    case ClosingState:
        newSocketState = QAbstractSocket::ClosingState;
        break;
    case UnconnectedState:
        newSocketState = QAbstractSocket::UnconnectedState;
        break;
    }
    setOpenMode(openMode);
    d->state = socketState;
    return d->unixSocket.setSocketDescriptor(socketDescriptor,
                                             newSocketState, openMode);
}

void QLocalSocketPrivate::_q_abortConnectionAttempt()
{
    Q_Q(QLocalSocket);
    q->close();
}

/*!
    Returns the native socket descriptor of the QLocalSocket object if
    this is available; otherwise returns -1.

    The socket descriptor is not available when QLocalSocket
    is in UnconnectedState.

    \sa setSocketDescriptor()
 */
quintptr QLocalSocket::socketDescriptor() const
{
    Q_D(const QLocalSocket);
    return d->unixSocket.socketDescriptor();
}

/*!
    \reimp
 */
qint64 QLocalSocket::readData(char *data, qint64 c)
{
    Q_D(QLocalSocket);
    return d->unixSocket.readData(data, c);
}

/*!
    \reimp
 */
qint64 QLocalSocket::writeData(const char *data, qint64 c)
{
    Q_D(QLocalSocket);
    return d->unixSocket.writeData(data, c);
}

/*!
    Aborts the current connection and resets the socket.
    Unlike disconnectFromServer(), this function immediately closes the socket,
    clearing any pending data in the write buffer.

    \sa disconnectFromServer(), close()
 */
void QLocalSocket::abort()
{
    Q_D(QLocalSocket);
    d->unixSocket.abort();
}

/*!
    \reimp
 */
qint64 QLocalSocket::bytesAvailable() const
{
    Q_D(const QLocalSocket);
    return QIODevice::bytesAvailable() + d->unixSocket.bytesAvailable();
}

/*!
    \reimp
 */
qint64 QLocalSocket::bytesToWrite() const
{
    Q_D(const QLocalSocket);
    return d->unixSocket.bytesToWrite();
}

/*!
    \reimp
 */
bool QLocalSocket::canReadLine() const
{
    Q_D(const QLocalSocket);
    return QIODevice::canReadLine() || d->unixSocket.canReadLine();
}

/*!
    \reimp
 */
void QLocalSocket::close()
{
    Q_D(QLocalSocket);
    d->unixSocket.close();
    if (d->delayConnect) {
        d->delayConnect->setEnabled(false);
        delete d->delayConnect;
        d->delayConnect = 0;
        d->connectTimer->stop();
        delete d->connectTimer;
        d->connectTimer = 0;
    }
    if (d->connectingSocket != -1)
        ::close(d->connectingSocket);
    d->connectingSocket = -1;
    d->connectingName = QString();
    d->connectingOpenMode = 0;
    d->serverName = QString();
    d->fullServerName = QString();
    QIODevice::close();
}

/*!
    \reimp
 */
bool QLocalSocket::waitForBytesWritten(int msecs)
{
    Q_D(QLocalSocket);
    return d->unixSocket.waitForBytesWritten(msecs);
}

/*!
    This function writes as much as possible from the internal write buffer
    to the socket, without blocking.  If any data was written, this function
    returns true; otherwise false is returned.

    Call this function if you need QLocalSocket to start sending buffered data
    immediately. The number of bytes successfully written depends on the
    operating system. In most cases, you do not need to call this function,
    because QLocalSocket will start sending data automatically once control
    goes back to the event loop. In the absence of an event loop, call
    waitForBytesWritten() instead.

    \sa write(), waitForBytesWritten()
 */
bool QLocalSocket::flush()
{
    Q_D(QLocalSocket);
    return d->unixSocket.flush();
}

/*!
    Attempts to close the socket. If there is pending data waiting to be
    written, QLocalSocket will enter ClosingState and wait until all data
    has been written. Eventually, it will enter UnconnectedState and emit
    the disconnectedFromServer() signal.

    \sa connectToServer()
*/
void QLocalSocket::disconnectFromServer()
{
    Q_D(QLocalSocket);
    d->unixSocket.disconnectFromHost();
}

/*!
    Returns the type of error that last occurred.

    \sa state(), errorString()
*/
QLocalSocket::LocalSocketError QLocalSocket::error() const
{
    Q_D(const QLocalSocket);
    switch (d->unixSocket.error()) {
    case QAbstractSocket::ConnectionRefusedError:
        return QLocalSocket::ConnectionRefusedError;
    case QAbstractSocket::RemoteHostClosedError:
        return QLocalSocket::PeerClosedError;
    case QAbstractSocket::HostNotFoundError:
        return QLocalSocket::ServerNotFoundError;
    case QAbstractSocket::SocketAccessError:
        return QLocalSocket::SocketAccessError;
    case QAbstractSocket::SocketResourceError:
        return QLocalSocket::SocketResourceError;
    case QAbstractSocket::SocketTimeoutError:
        return QLocalSocket::SocketTimeoutError;
    case QAbstractSocket::DatagramTooLargeError:
        return QLocalSocket::DatagramTooLargeError;
    case QAbstractSocket::NetworkError:
        return QLocalSocket::ConnectionError;
    case QAbstractSocket::UnsupportedSocketOperationError:
        return QLocalSocket::UnsupportedSocketOperationError;
    case QAbstractSocket::UnknownSocketError:
        return QLocalSocket::UnknownSocketError;
    default:
#if defined QLOCALSOCKET_DEBUG
        qWarning() << "QLocalSocket error not handled:" << d->unixSocket.error();
#endif
        break;
    }
    return UnknownSocketError;
}

/*!
    Returns true if the socket is valid and ready for use; otherwise
    returns false.

    Note: The socket's state must be ConnectedState before reading
    and writing can occur.

    \sa state()
 */
bool QLocalSocket::isValid() const
{
    Q_D(const QLocalSocket);
    return d->unixSocket.isValid();
}

/*!
    Returns the size of the internal read buffer. This limits the amount of
    data that the client can receive before you call read() or readAll().
    A read buffer size of 0 (the default) means that the buffer has no size
    limit, ensuring that no data is lost.

    \sa setReadBufferSize(), read()
 */
qint64 QLocalSocket::readBufferSize() const
{
    Q_D(const QLocalSocket);
    return d->unixSocket.readBufferSize();
}

/*!
    Sets the size of QLocalSocket's internal read buffer to be \a size bytes.

    If the buffer size is limited to a certain size, QLocalSocket won't
    buffer more than this size of data. Exceptionally, a buffer size of 0
    means that the read buffer is unlimited and all incoming data is buffered.
    This is the default.

    This option is useful if you only read the data at certain points in
    time (e.g., in a real-time streaming application) or if you want to
    protect your socket against receiving too much data, which may eventually
    cause your application to run out of memory.

    \sa readBufferSize(), read()
 */
void QLocalSocket::setReadBufferSize(qint64 size)
{
    Q_D(QLocalSocket);
    d->unixSocket.setReadBufferSize(size);
}

/*!
    Waits until the socket is connected, up to \a msec milliseconds. If the
    connection has been established, this function returns true; otherwise
    it returns false. In the case where it returns false, you can call
    error() to determine the cause of the error.

    The following example waits up to one second for a connection
    to be established:

    \snippet doc/src/snippets/code/src.network.socket.qlocalsocket_unix.cpp 0

    If msecs is -1, this function will not time out.

    \sa connectToServer(), connected()
 */
bool QLocalSocket::waitForConnected(int msec)
{
    Q_D(QLocalSocket);
    if (state() != ConnectingState)
        return (state() == ConnectedState);

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(d->connectingSocket, &readfds);

    timeval timeout;
    timeout.tv_sec = msec / 1000;
    timeout.tv_usec = (msec % 1000) * 1000;

    // timeout can not be 0 or else select will return an error.
    if (0 == msec)
        timeout.tv_usec = 1000;

    int result = -1;
    // on Linux timeout will be updated by select, but _not_ on other systems.
    QTime timer;
    timer.start();
    while (state() == ConnectingState
           && (-1 == msec || timer.elapsed() < msec)) {
        result = ::select(d->connectingSocket + 1, &readfds, 0, 0, &timeout);
        if (-1 == result && errno != EINTR) {
            d->errorOccurred( QLocalSocket::UnknownSocketError,
                    QLatin1String("QLocalSocket::waitForConnected"));
            break;
        }
        if (result > 0)
            d->_q_connectToSocket();
    }

    return (state() == ConnectedState);
}

/*!
    Waits until the socket has disconnected, up to \a msecs
    milliseconds. If the connection has been disconnected, this
    function returns true; otherwise it returns false. In the case
    where it returns false, you can call error() to determine
    the cause of the error.

    The following example waits up to one second for a connection
    to be closed:

    \snippet doc/src/snippets/code/src.network.socket.qlocalsocket_unix.cpp 1

    If msecs is -1, this function will not time out.

    \sa disconnectFromServer(), close()
*/
bool QLocalSocket::waitForDisconnected(int msecs)
{
    Q_D(QLocalSocket);
    if (state() == UnconnectedState) {
        qWarning() << "QLocalSocket::waitForDisconnected() is not allowed in UnconnectedState";
        return false;
    }
    return (d->unixSocket.waitForDisconnected(msecs));
}

/*!
    This function blocks until data is available for reading and the
    \l{QIODevice::}{readyRead()} signal has been emitted. The function
    will timeout after \a msecs milliseconds; the default timeout is
    30000 milliseconds.

    The function returns true if data is available for reading;
    otherwise it returns false (if an error occurred or the
    operation timed out).

    \sa waitForBytesWritten()
*/
bool QLocalSocket::waitForReadyRead(int msecs)
{
    Q_D(QLocalSocket);
    if (state() == QLocalSocket::UnconnectedState)
        return false;
    return (d->unixSocket.waitForReadyRead(msecs));
}

QT_END_NAMESPACE
