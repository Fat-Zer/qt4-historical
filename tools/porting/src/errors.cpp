/****************************************************************************
**
** Copyright (C) 2004-2007 Trolltech ASA. All rights reserved.
** Copyright (C) 2001-2004 Roberto Raggi
**
** This file is part of the qt3to4 porting application of the Qt Toolkit.
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

#include "errors.h"

QT_STATIC_CONST_IMPL Error& Errors::InternalError = Error( 1, -1, "Internal Error" );
QT_STATIC_CONST_IMPL Error& Errors::SyntaxError = Error( 2, -1, "Syntax Error before '%1'" );
QT_STATIC_CONST_IMPL Error& Errors::ParseError = Error( 3, -1, "Parse Error before '%1'" );
