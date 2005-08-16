/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the assistant application of the Qt Toolkit.
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

#ifndef PROFILE_H
#define PROFILE_H

#include <qfileinfo.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qmap.h>

class DocuParser;

class Profile
{
public:
    enum ProfileType { DefaultProfile, UserProfile };
    Profile();

    inline bool isValid() const;

    inline void addDCF( const QString &docfile );
    inline void addDCFIcon( const QString title, const QString &icon );
    inline void addDCFIndexPage( const QString title, const QString &indexPage );
    inline void addDCFImageDir( const QString title, const QString &imgDir );
    inline void addDCFTitle( const QString &dcf, const QString &title );
    inline void addProperty( const QString &name, const QString &value );
    inline bool hasDocFile( const QString &docFile );
    void removeDocFileEntry( const QString &title );

    inline ProfileType profileType() const { return type; }
    inline void setProfileType( ProfileType t ) { type = t; }

    inline DocuParser *docuParser() const { return dparser; }
    inline void setDocuParser( DocuParser *dp ) { dparser = dp; }

    static Profile* createDefaultProfile();
    static QString makeRelativePath( const QString &base, const QString &path );

    uint valid:1;
    ProfileType type;
    DocuParser *dparser;
    QMap<QString,QString> props;
    QMap<QString,QString> icons;
    QMap<QString,QString> indexPages;
    QMap<QString,QString> imageDirs;
    QMap<QString,QString> dcfTitles;
    QStringList docs;
};


inline bool Profile::isValid() const
{
    return valid;
}

inline void Profile::addDCFTitle(const QString &dcf, const QString &title)
{
    QString absdcf = QFileInfo(dcf).absoluteFilePath();
    dcfTitles[title] = absdcf;
    if (!docs.contains(absdcf))
        docs << absdcf;
}

inline void Profile::addDCF( const QString &docfile )
{
    if( !docs.contains( docfile ) == 0 )
        docs << docfile;
}

inline void Profile::addDCFIcon( const QString docfile,
                                     const QString &icon )
{
    icons[docfile] = icon;
}

inline void Profile::addDCFIndexPage( const QString title,
                                      const QString &indexPage )
{
    indexPages[title] = indexPage;
}

inline void Profile::addDCFImageDir( const QString docfile,
                                     const QString &imgDir )
{
    imageDirs[docfile] = imgDir;
}

inline void Profile::addProperty( const QString &name,
                                  const QString &value )
{
    props[name] = value;
}

inline bool Profile::hasDocFile( const QString &name )
{
    return docs.contains( name );
}

#endif
