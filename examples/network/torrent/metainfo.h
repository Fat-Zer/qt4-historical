/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#ifndef METAINFO_H
#define METAINFO_H

#include <QByteArray>
#include <QDateTime>
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariant>

struct MetaInfoSingleFile
{
    qint64 length;
    QByteArray md5sum;
    QString name;
    int pieceLength;
    QList<QByteArray> sha1Sums;
};

struct MetaInfoMultiFile
{
    qint64 length;
    QByteArray md5sum;
    QString path;
};

class MetaInfo
{
public:
    enum FileForm {
        SingleFileForm,
        MultiFileForm
    };

    MetaInfo();
    void clear();

    bool parse(const QByteArray &data);
    QString errorString() const;

    QByteArray infoValue() const;

    FileForm fileForm() const;
    QString announceUrl() const;
    QStringList announceList() const;
    QDateTime creationDate() const;
    QString comment() const;
    QString createdBy() const;

    // For single file form
    MetaInfoSingleFile singleFile() const;

    // For multifile form
    QList<MetaInfoMultiFile> multiFiles() const;
    QString name() const;
    int pieceLength() const;
    QList<QByteArray> sha1Sums() const;

    // Total size
    qint64 totalSize() const;

private: 
    QString errString;
    QByteArray content;
    QByteArray infoData;

    FileForm metaInfoFileForm;
    MetaInfoSingleFile metaInfoSingleFile;
    QList<MetaInfoMultiFile> metaInfoMultiFiles;
    QString metaInfoAnnounce;
    QStringList metaInfoAnnounceList;
    QDateTime metaInfoCreationDate;
    QString metaInfoComment;
    QString metaInfoCreatedBy;
    QString metaInfoName;
    int metaInfoPieceLength;
    QList<QByteArray> metaInfoSha1Sums;
};

#endif
