/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt 3 compatibility classes of the Qt Toolkit.
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

#include "q3network.h"

#ifndef QT_NO_NETWORK

#include "q3networkprotocol.h"

// protocols
#include "q3ftp.h"
#include "q3http.h"

/*!
    \relates Q3UrlOperator

    This function registers the network protocols for FTP and HTTP.
    You must call this function before you use QUrlOperator for
    these protocols.
*/
void q3InitNetworkProtocols()
{
#ifndef QT_NO_NETWORKPROTOCOL_FTP
    Q3NetworkProtocol::registerNetworkProtocol( "ftp", new Q3NetworkProtocolFactory< Q3Ftp > );
#endif
#ifndef QT_NO_NETWORKPROTOCOL_HTTP
    Q3NetworkProtocol::registerNetworkProtocol( "http", new Q3NetworkProtocolFactory< Q3Http > );
#endif
}

#endif // QT_NO_NETWORK
