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

#ifndef Q3ICONVIEW_EXTRAINFO_H
#define Q3ICONVIEW_EXTRAINFO_H

#include <QtDesigner/QDesignerExtraInfoExtension>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QExtensionFactory>

#include <QtCore/QPointer>

class Q3IconView;
class Q3IconViewItem;
class DomItem;

class Q3IconViewExtraInfo: public QObject, public QDesignerExtraInfoExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerExtraInfoExtension)
public:
    Q3IconViewExtraInfo(Q3IconView *widget, QDesignerFormEditorInterface *core, QObject *parent);

    virtual QWidget *widget() const;
    virtual QDesignerFormEditorInterface *core() const;

    virtual bool saveUiExtraInfo(DomUi *ui);
    virtual bool loadUiExtraInfo(DomUi *ui);

    virtual bool saveWidgetExtraInfo(DomWidget *ui_widget);
    virtual bool loadWidgetExtraInfo(DomWidget *ui_widget);

    void initializeQ3IconViewItems(const QList<DomItem *> &items);

private:
    QPointer<Q3IconView> m_widget;
    QPointer<QDesignerFormEditorInterface> m_core;
};

class Q3IconViewExtraInfoFactory: public QExtensionFactory
{
    Q_OBJECT
public:
    Q3IconViewExtraInfoFactory(QDesignerFormEditorInterface *core, QExtensionManager *parent = 0);

protected:
    virtual QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;

private:
    QDesignerFormEditorInterface *m_core;
};

#endif // Q3ICONVIEW_EXTRAINFO_H
