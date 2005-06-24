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

#include "logger.h"
#include <iostream>
#include <QFile>


LogEntry::LogEntry(QString type, QString location)
:type(type), location(location)
{}

PlainLogEntry::PlainLogEntry(QString type, QString location, QString text)
:LogEntry(type, location), text(text)
{}

SourcePointLogEntry::SourcePointLogEntry(QString type, QString location, QString file, int line, int column, QString text)
:LogEntry(type, location), file(file), line(line), column(column), text(text)
{}

QString SourcePointLogEntry::description() const
{
    return "In file "  + file +
           " at line " + QString("%1").arg(line + 1) + //line count is zero based, adjust here.
           " column "  + QString("%1").arg(column) +
           ": " + text ;
}

void SourcePointLogEntry::updateLinePos(int threshold,  int delta)
{
    if (line >= threshold)
        line += delta;
}

/////////////////////////////////////////////////////


Logger::~Logger()
{
   qDeleteAll(logEntries);
}

Logger *Logger::theInstance  = 0;
Logger *Logger::instance()
{
    if(!theInstance)
        theInstance = new Logger();
        return theInstance;
}

void Logger::deleteInstance()
{
    if(theInstance)
        delete theInstance;
}

void Logger::addEntry(LogEntry *entry)
{
   Q_ASSERT(entry);
   pendingLogEntries.append(entry);
}

void Logger::beginSection()
{
    commitSection();
}

void Logger::commitSection()
{
    logEntries += pendingLogEntries;
    pendingLogEntries.clear();
}

void Logger::revertSection()
{
    qDeleteAll(pendingLogEntries);
    pendingLogEntries.clear();
}

int Logger::numEntries()
{
    commitSection();
    return logEntries.size();
}

QStringList Logger::fullReport()
{
    commitSection();
    QStringList report;
    report << "Number of log entries: " + QString("%1").arg(logEntries.size());
    foreach(LogEntry *logEntry, logEntries) {
        report << logEntry->description();
    }
    return report;
}

/*
    Update the line for all SourcePointLogEntrys in the list of pending log
    entries located on or after insertLine.
*/
void Logger::updateLineNumbers(int insertLine, int numLines)
{
    foreach(LogEntry *logEntry, pendingLogEntries) {
        logEntry->updateLinePos(insertLine, numLines);
    }
}
