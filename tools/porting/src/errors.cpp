/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
** Copyright (C) 2001-2004 Roberto Raggi
**
** This file is part of the porting application of the Qt Toolkit.
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
#include "errors.h"

QT_STATIC_CONST_IMPL Error& Errors::InternalError = Error( 1, -1, "Internal Error" );
QT_STATIC_CONST_IMPL Error& Errors::SyntaxError = Error( 2, -1, "Syntax Error before '%1'" );
QT_STATIC_CONST_IMPL Error& Errors::ParseError = Error( 3, -1, "Parse Error before '%1'" );
