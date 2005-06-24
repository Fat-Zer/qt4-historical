/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the porting application of the Qt Toolkit.
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

#ifndef PROJECTPORTER_H
#define PROJECTPORTER_H

#include <QString>
#include <QSet>
#include "fileporter.h"
#include "preprocessorcontrol.h"

class ProjectPorter : public QObject
{
Q_OBJECT
public:
    ProjectPorter(QString basePath, QStringList includeDirectories, QStringList qt3HeadersFilenames = QStringList());
    void enableCppParsing(bool enable);
    void enableMissingFilesWarnings(bool enable);
    void portProject(QString filePath);
    void portFile(QString filePath);
private slots:
    void error(QString type, QString text);
private:
    void portProject(QString inPath, QString proFileName);
    void portProFile(QString fileName, QMap<QString, QString> tagMap);
    void portFiles(QString basePath, QStringList fileNames);
    void enableAttributes(const IncludeFiles &includeFiles, const QString &fileName);

    QSet<QString> processedFilesSet;
    QString basePath;
    QStringList includeDirectories;
    PreprocessorCache preprocessorCache;
    Rpp::DefineMap *defaultDefinitions;
    FilePorter filePorter;
    QStringList qt3HeadersFilenames;
    bool analyze;
    bool warnings;
};

#endif
