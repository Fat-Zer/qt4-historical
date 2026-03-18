/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef SDK_GLOBAL_H
#define SDK_GLOBAL_H

#include <QtCore/qglobal.h>

#define QT_SDK_EXTERN Q_DECL_EXPORT
#define QT_SDK_IMPORT Q_DECL_IMPORT

#ifdef QT_DESIGNER_STATIC
#  define QT_SDK_EXPORT
#elif defined(QT_SDK_LIBRARY)
#  define QT_SDK_EXPORT QT_SDK_EXTERN
#else
#  define QT_SDK_EXPORT QT_SDK_IMPORT
#endif

#endif // SDK_GLOBAL_H
