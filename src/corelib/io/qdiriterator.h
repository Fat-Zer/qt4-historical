/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QDIRITERATOR_H
#define QDIRITERATOR_H

#include <QtCore/qdir.h>

QT_BEGIN_HEADER

QT_MODULE(Core)

class QDirIteratorPrivate;
class Q_CORE_EXPORT QDirIterator {
public:
    enum IteratorFlag {
        NoIteratorFlags = 0x0,
        FollowSymlinks = 0x1,
        Subdirectories = 0x2
    };
    Q_DECLARE_FLAGS(IteratorFlags, IteratorFlag)

    QDirIterator(const QDir &dir, IteratorFlags flags = NoIteratorFlags);
    QDirIterator(const QString &path,
                 IteratorFlags flags = NoIteratorFlags);
    QDirIterator(const QString &path,
                 QDir::Filters filter,
                 IteratorFlags flags = NoIteratorFlags);
    QDirIterator(const QString &path,
                 const QStringList &nameFilters,
                 QDir::Filters filters = QDir::NoFilter,
                 IteratorFlags flags = NoIteratorFlags);

    virtual ~QDirIterator();

    QString next();
    bool hasNext() const;

    QString fileName() const;
    QString filePath() const;
    QFileInfo fileInfo() const;
    QString path() const;

private:
    Q_DISABLE_COPY(QDirIterator)

    QDirIteratorPrivate *d;
    friend class QDir;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDirIterator::IteratorFlags)

QT_END_HEADER

#endif
