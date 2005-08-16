/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
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

#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QMap>
/*
    Base class for logger entries;
    description() should return a text for this entry,
*/
class LogEntry
{
public:
    LogEntry(QString type, QString location);
    virtual ~LogEntry(){};
    virtual QString description() const =0;
    virtual void updateLinePos(int threshold, int delta) {Q_UNUSED(threshold); Q_UNUSED(delta)};
protected:
    QString type; // Error, Warning, Info, etc
    QString location;// preprocessor, c++parser, porting, etc
};

class PlainLogEntry: public LogEntry
{
public:
     PlainLogEntry(QString type, QString lcation, QString text);
     QString description() const {return text;};
protected:
     QString text;
};

/*
    A log entry that stores a source point: file, line and column.
*/
class SourcePointLogEntry : public LogEntry
{
public:
    SourcePointLogEntry(QString type, QString location, QString file, int line, int column, QString text);
    QString description() const;
    void updateLinePos(int threshold, int delta);
protected:
    QString file;
    int line;
    int column;
    QString text;
};


class Logger
{
public:
    Logger(){};
    ~Logger();
    static Logger *instance();
    static void deleteInstance();

    void beginSection();
    void commitSection();
    void revertSection();
    void addEntry(LogEntry *entry);

    QStringList fullReport();
    int numEntries();
    void updateLineNumbers(int insertLine, int numLines);
    /*
        glabalState can be used for storage of application state
        together with the logger. This can be useful in some cases,
        for example the current filename is stored here when processing
        files.
    */
    QMap<QString, QString> globalState;
private:
    static Logger *theInstance;
    QList<LogEntry*> logEntries;
    QList<LogEntry*> pendingLogEntries;
};


#endif
