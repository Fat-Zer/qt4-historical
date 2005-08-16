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

#ifndef QDESIGNER_SETTINGS_H
#define QDESIGNER_SETTINGS_H

#include <QtCore/QRect>
#include <QtCore/QSettings>

class QDesignerSettings : public QSettings
{
public:
    QDesignerSettings();
    virtual ~QDesignerSettings();

    QStringList formTemplatePaths() const;
    void setFormTemplatePaths(const QStringList &paths);

    QString defaultUserWidgetBoxXml() const;

    void setGeometryFor(QWidget *w, const QRect &fallBack = QRect()) const;
    void saveGeometryFor(const QWidget *w);

    QStringList recentFilesList() const;
    void setRecentFilesList(const QStringList &list);

    void setShowNewFormOnStartup(bool showIt);
    bool showNewFormOnStartup() const;

    void setUIMode(int mode);
    int uiMode() const;

    void setUseBigIcons(bool useBig);
    bool useBigIcons() const;

    QByteArray mainWindowState() const;
    void setMainWindowState(const QByteArray &mainWindowState);

private:
    QStringList defaultFormTemplatePaths() const;

    void setGeometryHelper(QWidget *w, const QString &key, const QRect &fallBack) const;
    void saveGeometryHelper(const QWidget *w, const QString &key);

private:
    QString m_designerPath;
};

#endif // QDESIGNER_SETTINGS_H
