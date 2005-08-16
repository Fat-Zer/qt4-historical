/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef DEPLOYMENT_INCL
#define DEPLOYMENT_INCL

#include <qstring.h>
#include <qlist.h>
#include <project.h>

class AbstractRemoteConnection;

struct CopyItem
{
    CopyItem(const QString& f, const QString& t) : from(f) , to(t) { }
    QString from;
    QString to;
};
typedef QList<CopyItem> DeploymentList;

class DeploymentHandler
{
public:
    inline void setConnection(AbstractRemoteConnection*);
    inline AbstractRemoteConnection* connection() const;
    bool deviceCopy(const DeploymentList &deploymentList);
    bool deviceDeploy(const DeploymentList &deploymentList);
    void cleanup(const DeploymentList &deploymentList);
    static void initProjectDeploy(QMakeProject* project, DeploymentList &deploymentList, const QString &testPath = "\\Program Files\\qt_test");
    static void initQtDeploy(QMakeProject* project, DeploymentList &deploymentList, const QString &testPath = "\\Program Files\\qt_test");
private:
    AbstractRemoteConnection* m_connection;
};

inline void DeploymentHandler::setConnection(AbstractRemoteConnection *connection) { m_connection = connection; }
inline AbstractRemoteConnection* DeploymentHandler::connection() const { return m_connection; }
#endif