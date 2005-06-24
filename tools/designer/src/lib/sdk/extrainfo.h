/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the designer application of the Qt Toolkit.
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

#ifndef EXTRAINFO_H
#define EXTRAINFO_H

#include <QtDesigner/sdk_global.h>
#include <QtDesigner/extension.h>

class DomWidget;
class DomUi;
class QWidget;

class QDesignerFormEditorInterface;

class QT_SDK_EXPORT QDesignerExtraInfoExtension
{
public:
    virtual ~QDesignerExtraInfoExtension() {}

    virtual QDesignerFormEditorInterface *core() const = 0;
    virtual QWidget *widget() const = 0;

    virtual bool saveUiExtraInfo(DomUi *ui) = 0;
    virtual bool loadUiExtraInfo(DomUi *ui) = 0;

    virtual bool saveWidgetExtraInfo(DomWidget *ui_widget) = 0;
    virtual bool loadWidgetExtraInfo(DomWidget *ui_widget) = 0;

    QString workingDirectory() const;
    void setWorkingDirectory(const QString &workingDirectory);

private:
    QString m_workingDirectory;
};
Q_DECLARE_EXTENSION_INTERFACE(QDesignerExtraInfoExtension, "com.trolltech.Qt.Designer.ExtraInfo")


#endif // EXTRAINFO_H
