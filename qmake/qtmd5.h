/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the qmake application of the Qt Toolkit.
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

/*
    Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
    rights reserved.

    RSA Data Security, Inc. makes no representations concerning either
    the merchantability of this software or the suitability of this
    software for any particular purpose. It is provided "as is"
    without express or implied warranty of any kind.

    License to copy and use this software is granted provided that it
    is identified as the "RSA Data Security, Inc. MD5 Message-Digest
    Algorithm" in all material mentioning or referencing this software
    or this function.

    License is also granted to make and use derivative works provided
    that such works are identified as "derived from the RSA Data
    Security, Inc. MD5 Message-Digest Algorithm" in all material
    mentioning or referencing the derived work.

    These notices must be retained in any copies of any part of this
    documentation and/or software.
*/

#ifndef QTMD5_H
#define QTMD5_H

#include <qstring.h>
#include <qbytearray.h>

void qtMD5(const QByteArray &src, unsigned char *digest);
QString qtMD5(const QByteArray &src);

#endif // QTMD5_H
