/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the core module of the Qt Toolkit.
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
#ifndef __QRESOURCE_P_H__
#define __QRESOURCE_P_H__

#include <qfileengine.h>

class QResourceFileEnginePrivate;
class QResourceFileEngine : public QFileEngine
{
private:
    Q_DECLARE_PRIVATE(QResourceFileEngine)
public:
    explicit QResourceFileEngine(const QString &path);
    ~QResourceFileEngine();

    virtual void setFileName(const QString &file);

    virtual bool open(int flags) ;
    virtual bool close();
    virtual void flush();
    virtual qint64 size() const;
    virtual qint64 at() const;
    virtual bool atEnd() const;
    virtual bool seek(qint64);
    virtual int ungetch(int);
    virtual qint64 read(char *data, qint64 maxlen);
    virtual qint64 write(const char *data, qint64 len);

    virtual bool remove();
    virtual bool copy(const QString &newName);
    virtual bool rename(const QString &newName);
    virtual bool link(const QString &newName);

    virtual bool isSequential() const;

    virtual bool isRelativePath() const;

    virtual bool mkdir(const QString &dirName, bool createParentDirectories) const;
    virtual bool rmdir(const QString &dirName, bool recurseParentDirectories) const;

    virtual bool setSize(qint64 size);

    virtual QStringList entryList(QDir::Filters filters, const QStringList &filterNames) const;

    virtual bool caseSensitive() const;

    virtual FileFlags fileFlags(FileFlags type) const;

    virtual bool chmod(uint perms);

    virtual QString fileName(QFileEngine::FileName file) const;

    virtual uint ownerId(FileOwner) const;
    virtual QString owner(FileOwner) const;

    virtual QDateTime fileTime(FileTime time) const;

    virtual Type type() const;
};

#endif /* __QRESOURCE_P_H__ */
