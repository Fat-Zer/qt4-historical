/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
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

#if (defined(_WIN32) || defined(__NT__))
#  define QT_UNDEF_MACROS_IN_PCH
#  define _WINSCARD_H_
#  define _POSIX_         /* Make sure PATH_MAX et al. are defined    */
#  include <limits.h>
#  undef _POSIX_          /* Don't polute                             */

   /* Make sure IP v6 is defined first of all, before windows.h     */
#  ifndef QT_NO_IPV6
#     include <winsock2.h>
#  endif
#  include <stdlib.h>
#endif

#if defined __cplusplus
#include <qglobal.h>
#include <qlist.h>
#include <qvariant.h>  // All moc genereated code has this include
#include <qplatformdefs.h>
#include <qregexp.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtextcodec.h>

#include <limits.h>
#include <stdlib.h>
#endif

#if defined(QT_UNDEF_MACROS_IN_PCH)
#  undef max /*  These are defined in windef.h, but                   */
#  undef min /*  we don't want them when building Qt                  */
#  undef _WINSCARD_H_
#endif
