/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef UIC_H
#define UIC_H

#include "databaseinfo.h"
#include "customwidgetsinfo.h"

#include <qstring.h>
#include <qstringlist.h>
#include <qhash.h>
#include <qstack.h>

class QTextStream;
class QIODevice;

class Driver;
class DomUI;
class DomWidget;
class DomSpacer;
class DomLayout;
class DomLayoutItem;
class DomItem;

struct Option;

class Uic
{
public:
    Uic(Driver *driver);
    ~Uic();

    bool printDependencies();

    inline Driver *driver() const
    { return drv; }

    inline QTextStream &output()
    { return out; }

    inline const Option &option() const
    { return opt; }

    inline QString pixmapFunction() const
    { return pixFunction; }

    inline void setPixmapFunction(const QString &f)
    { pixFunction = f; }

    inline bool hasExternalPixmap() const
    { return externalPix; }

    inline void setExternalPixmap(bool b)
    { externalPix = b; }

    inline const DatabaseInfo *databaseInfo() const
    { return &info; }

    inline const CustomWidgetsInfo *customWidgetsInfo() const
    { return &cWidgetsInfo; }

    bool write(QIODevice *in);
    bool write(DomUI *ui);

    bool isMainWindow(const QString &className) const;
    bool isToolBar(const QString &className) const;
    bool isStatusBar(const QString &className) const;
    bool isButton(const QString &className) const;
    bool isContainer(const QString &className) const;
    bool isMenuBar(const QString &className) const;
    bool isMenu(const QString &className) const;

private:
    // copyright header
    void writeCopyrightHeader(DomUI *ui);

    // header protection
    void writeHeaderProtectionStart();
    void writeHeaderProtectionEnd();

private:
    Driver *drv;
    QTextStream &out;
    const Option &opt;
    DatabaseInfo info;
    CustomWidgetsInfo cWidgetsInfo;
    QString pixFunction;
    bool externalPix;
};

#endif // UIC_H
