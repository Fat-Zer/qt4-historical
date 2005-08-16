/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/
#ifndef CE_SDK_HANDLER_INCL
#define CE_SDK_HANDLER_INCL

#include <QStringList>
#include <QDir>

QT_USE_NAMESPACE

#define VCINSTALL_MACRO "$(VCInstallDir)"
#define VSINSTALL_MACRO "$(VSInstallDir)"

class CeSdkInfo
{
public:
    CeSdkInfo();
    inline QString                  name();
    inline QString                  binPath();
    inline QString                  includePath();
    inline QString                  libPath();
    QStringList                     environment();
    inline bool                     isValid();
    inline int                      majorVersion();
    inline int                      minorVersion();
    inline bool                     isSupported();
private:
    friend class                    CeSdkHandler;
    QString                         m_name;
    QString                         m_bin;
    QString                         m_include;
    QString                         m_lib;
    int                             m_major;
    int                             m_minor;
};

inline QString CeSdkInfo::name(){ return m_name; }
inline QString CeSdkInfo::binPath(){ return m_bin; }
inline QString CeSdkInfo::includePath(){ return m_include; }
inline QString CeSdkInfo::libPath(){ return m_lib; }
inline bool CeSdkInfo::isValid(){ return !m_name.isEmpty() && !m_bin.isEmpty() && !m_include.isEmpty() && !m_lib.isEmpty(); }
inline int CeSdkInfo::majorVersion(){ return m_major; }
inline int CeSdkInfo::minorVersion(){ return m_minor; }
inline bool CeSdkInfo::isSupported() { return m_major >= 5; }

class CeSdkHandler
{
public:
                                    CeSdkHandler();
    bool                            parse();
    inline QList<CeSdkInfo>         listAll() const;
    CeSdkInfo                       find(const QString &name);
private:
    inline QString                  fixPaths(QString path) const;
    QList<CeSdkInfo>                m_list;
    QString                         VCInstallDir;
    QString                         VSInstallDir;
};

inline QList<CeSdkInfo> CeSdkHandler::listAll() const
{
    return m_list;
}

inline QString CeSdkHandler::fixPaths(QString path) const
{
    QString str = QDir::toNativeSeparators(QDir::cleanPath(path.replace(VCINSTALL_MACRO, VCInstallDir).replace(VSINSTALL_MACRO, VSInstallDir).replace(QLatin1String("$(PATH)"), QLatin1String("%PATH%"))));
    if (str.endsWith(';'))
        str.truncate(str.length() - 1);
    return str;
}

#endif
