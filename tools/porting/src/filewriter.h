/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
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

QByteArray detectLineEndings(const QByteArray &array);

#endif
