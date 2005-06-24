/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the core module of the Qt Toolkit.
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

#include "qcoreapplication.h"
#include <private/qcore_mac_p.h>

/*****************************************************************************
  QCoreApplication utility functions
 *****************************************************************************/
QString qAppName()                                // get application name
{
    static QString appName;
    QCoreApplication *app;
    if (appName.isEmpty() && (app = QCoreApplication::instance())) {
        char *p = strrchr(app->argv()[0], '/');
        appName = p ? QString::fromUtf8(p + 1) : QString::fromUtf8(app->argv()[0]);
    }
    return appName;
}

QString qAppFileName()
{
    static QString appFileName;
    if (appFileName.isEmpty()) {
        QCFType<CFURLRef> bundleURL(CFBundleCopyExecutableURL(CFBundleGetMainBundle()));
        QCFString cfPath(CFURLCopyFileSystemPath(bundleURL, kCFURLPOSIXPathStyle));
        appFileName = cfPath;
    }
    return appFileName;
}

