/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
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

#ifndef QSHAREDMEMORY_P_H
#define QSHAREDMEMORY_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of qapplication_qws.cpp and qgfxvnc_qws.cpp.  This header file may
// change from version to version without notice, or even be removed.
//
// We mean it.
//

#if !defined (QT_QWS_NO_SHM)

#include "qplatformdefs.h"
#include "qstring.h"

class QSharedMemory {
public:
        QSharedMemory() {};
        QSharedMemory(int, const QString &, char c = 'Q');
        ~QSharedMemory() {};

        bool create();
        void destroy();

        bool attach();
        void detach();

        void setPermissions(mode_t mode);
        int size();
        void * base() { return shmBase; };

private:
        void *shmBase;
        int shmSize;
        QString shmFile;
        char character;
#if defined(QT_POSIX_QSHM)
        int shmFD;
#else
        int shmId;
        key_t key;
        int idInitted;
#endif
};

#endif

#endif // QSHAREDMEMORY_P_H
