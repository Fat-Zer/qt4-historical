/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
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

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QMap>
#include <QString>
#include <QByteArray>

class FileWriter
{
public:
    enum OverWriteFiles{DontOverWrite, AlwaysOverWrite, AskOnOverWrite};
    enum WriteResult { WriteFailed = 0, WriteSucceeded = 1, WriteSkipped };
    static FileWriter *instance();
    static void deleteInstance();

    FileWriter(OverWriteFiles overWRite = AskOnOverWrite,
                QString overwriteMessage = QString());
    WriteResult writeFile(QString filePath, QByteArray contents);
    WriteResult writeFileVerbously(QString filePath, QByteArray contents);
    void setOverwriteFiles(OverWriteFiles writeMode);
private:
    QMap<QString, int> processedFilesSet;
    OverWriteFiles overWriteFiles;
    QString overwriteMessage;
    static FileWriter *theInstance;
};

#endif
