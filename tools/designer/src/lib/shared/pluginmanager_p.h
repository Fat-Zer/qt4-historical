/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "shared_global_p.h"

#include <QtCore/QStringList>
#include <QtCore/QSettings>

class QDesignerFormEditorInterface;
class QDesignerCustomWidgetInterface;

class QT_SHARED_EXPORT PluginManager: public QObject
{
    Q_OBJECT
public:
    PluginManager(QDesignerFormEditorInterface *core);
    virtual ~PluginManager();

    QDesignerFormEditorInterface *core() const;

    QObject *instance(const QString &plugin) const;

    QStringList registeredPlugins() const;

    QStringList findPlugins(const QString &path);

    QStringList pluginPaths() const;
    void setPluginPaths(const QStringList &plugin_paths);

    QStringList disabledPlugins() const;
    void setDisabledPlugins(const QStringList &disabled_plugins);

    QList<QObject*> instances() const;
    QList<QDesignerCustomWidgetInterface*> registeredCustomWidgets() const;

public slots:
    bool syncSettings();
    void ensureInitialized();

private:
    void updateRegisteredPlugins();
    void registerPath(const QString &path);
    void registerPlugin(const QString &plugin);

private:
    QDesignerFormEditorInterface *m_core;
    QStringList m_pluginPaths;
    QStringList m_registeredPlugins;
    QStringList m_disabledPlugins;
    QList<QDesignerCustomWidgetInterface*> m_customWidgets;

    QStringList defaultPluginPaths() const;
};

#endif // PLUGINMANAGER_H
