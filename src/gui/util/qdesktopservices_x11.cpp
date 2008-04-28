/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
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

#include "qdesktopservices.h"

#ifndef QT_NO_DESKTOPSERVICES

#include <qprocess.h>
#include <qurl.h>
#include <qdir.h>
#include <qfile.h>
#include <qtextstream.h>
#include <private/qt_x11_p.h>
#include <qcoreapplication.h>
#include <stdlib.h>

QT_BEGIN_NAMESPACE

inline static bool launch(const QUrl &url, const QString &client)
{
    return (QProcess::startDetached(client + QLatin1Char(' ') + QString::fromLatin1(url.toEncoded().constData())));
}

static bool openDocument(const QUrl &url)
{
    if (!url.isValid())
        return false;

    if (launch(url, QLatin1String("xdg-open")))
        return true;

    if (X11->desktopEnvironment == DE_GNOME && launch(url, QLatin1String("gnome-open"))) {
        return true;
    } else {
        if (X11->desktopEnvironment == DE_KDE && launch(url, QLatin1String("kfmclient exec")))
            return true;
    }

    if (launch(url, QLatin1String("firefox")))
        return true;
    if (launch(url, QLatin1String("mozilla")))
        return true;
    if (launch(url, QLatin1String("netscape")))
        return true;
    if (launch(url, QLatin1String("opera")))
        return true;

    return false;
}

static bool launchWebBrowser(const QUrl &url)
{
    if (!url.isValid())
        return false;
    if (url.scheme() == QLatin1String("mailto"))
        return openDocument(url);

    if (launch(url, QLatin1String("xdg-open")))
        return true;
    if (launch(url, QString::fromLocal8Bit(getenv("DEFAULT_BROWSER"))))
        return true;
    if (launch(url, QString::fromLocal8Bit(getenv("BROWSER"))))
        return true;

    if (X11->desktopEnvironment == DE_GNOME && launch(url, QLatin1String("gnome-open"))) {
        return true;
    } else {
        if (X11->desktopEnvironment == DE_KDE && launch(url, QLatin1String("kfmclient openURL")))
            return true;
    }

    if (launch(url, QLatin1String("firefox")))
        return true;
    if (launch(url, QLatin1String("mozilla")))
        return true;
    if (launch(url, QLatin1String("netscape")))
        return true;
    if (launch(url, QLatin1String("opera")))
        return true;
    return false;
}



/*!
    \enum QDesktopServices::StandardLocation
    \since 4.4

    This enum describes the different locations that can be queried
    by QDesktopServices::storageLocation and QDesktopServices::displayName.

    \value DesktopLocation Returns the users desktop.
    \value DocumentsLocation Returns the users document.
    \value FontsLocation Returns the users fonts.
    \value ApplicationsLocation Returns the users applications.
    \value MusicLocation Returns the users music.
    \value MoviesLocation Returns the users movies.
    \value PicturesLocation Returns the users pictures.
    \value TempLocation Returns the system's temporary directory.
    \value HomeLocation Returns the user's home directory.
    \value DataLocation Returns a directory location where persistent application
           data can be stored.  QCoreApplication::applicationName and
           QCoreApplication::organizationName should be set to work
           on all platforms.

    \sa storageLocation() displayName()
*/


/*!
    \fn QString QDesktopServices::storageLocation(StandardLocation type)
    \since 4.4

    Returns the default system directory where files of \a type belong or an empty string
    if it is unable to determine the location.

    Note: that storage location returned can be a directory that doesn't exists.
  */
QString QDesktopServices::storageLocation(StandardLocation type)
{
    if (type == QDesktopServices::HomeLocation)
        return QDir::homePath();
    if (type == QDesktopServices::TempLocation)
        return QDir::tempPath();

    if (type == QDesktopServices::DataLocation) {
        // http://standards.freedesktop.org/basedir-spec/basedir-spec-0.6.html
        QString xdgDataHome = QLatin1String(qgetenv("XDG_DATA_HOME"));
        if (xdgDataHome.isEmpty())
            xdgDataHome = QDir::homePath() + QLatin1String("/.local/share");
        xdgDataHome += QLatin1String("/data/")
                    + QCoreApplication::organizationName() + QLatin1Char('/')
                    + QCoreApplication::applicationName();
        return xdgDataHome;
    }

    // http://www.freedesktop.org/wiki/Software/xdg-user-dirs
    QString xdgConfigHome = QLatin1String(qgetenv("XDG_CONFIG_HOME"));
    if (xdgConfigHome.isEmpty())
        xdgConfigHome = QDir::homePath() + QLatin1String("/.config");
    QFile file(xdgConfigHome + QLatin1String("/user-dirs.dirs"));
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QHash<QString, QString> lines;
        QTextStream stream(&file);
        // Only look for lines like: XDG_DESKTOP_DIR="$HOME/Desktop"
        QRegExp exp(QLatin1String("^XDG_(.*)_DIR=(.*)$"));
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            if (exp.indexIn(line) != -1) {
                QStringList lst = exp.capturedTexts();
                QString key = lst.at(1);
                QString value = lst.at(2);
                if (value.length() > 2
                    && value.left(1) == QLatin1String("\"")
                    && value.right(1) == QLatin1String("\""))
                    value = value.mid(1, value.length() - 2);
                // Store the key and value: "DESKTOP", "$HOME/Desktop"
                lines[key] = value;
            }
        }

        QString key;
        switch (type) {
        case DesktopLocation: key = QLatin1String("DESKTOP"); break;
        case DocumentsLocation: key = QLatin1String("DOCUMENTS"); break;
        case PicturesLocation: key = QLatin1String("PICTURES"); break;
        case MusicLocation: key = QLatin1String("MUSIC"); break;
        case MoviesLocation: key = QLatin1String("VIDEOS"); break;
        default: break;
        }
        if (!key.isEmpty() && lines.contains(key)) {
            QString value = lines[key];
            // value can start with $HOME
            if (value.startsWith(QLatin1String("$HOME")))
                value = QDir::homePath() + value.mid(5);
            return value;
        }
    }

    QDir emptyDir;
    QString path;
    switch (type) {
    case DesktopLocation:
        path = QDir::homePath() + QLatin1String("/Desktop");
        break;
    case DocumentsLocation:
        path = QDir::homePath() + QLatin1String("/Documents");
       break;
    case PicturesLocation:
        path = QDir::homePath() + QLatin1String("/Pictures");
        break;

    case FontsLocation:
        path = QDir::homePath() + QLatin1String("/.fonts");
        break;

    case MusicLocation:
        path = QDir::homePath() + QLatin1String("/Music");
        break;

    case MoviesLocation:
        path = QDir::homePath() + QLatin1String("/Movies");
        break;

    case ApplicationsLocation:
    default:
        break;
    }

    if (emptyDir.exists(path))
        return path;

    return QString();
}

/*!
    \fn QString QDesktopServices::displayName(const StandardLocation type)

    Returns a localized display name for a location \a type or
    an empty QString if it is unable to figure out.
  */
QString QDesktopServices::displayName(StandardLocation type)
{
    Q_UNUSED(type);
    return QString();
}

QT_END_NAMESPACE

#endif // QT_NO_DESKTOPSERVICES
