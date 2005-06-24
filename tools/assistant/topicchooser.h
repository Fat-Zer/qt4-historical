/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the assistant application of the Qt Toolkit.
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

#ifndef TOPICCHOOSER_H
#define TOPICCHOOSER_H

#include "ui_topicchooser.h"

#include <qdialog.h>
#include <qstringlist.h>

class TopicChooser : public QDialog
{
    Q_OBJECT
public:
    TopicChooser(QWidget *parent, const QStringList &lnkNames,
                  const QStringList &lnks, const QString &title);

    QString link() const;

    static QString getLink(QWidget *parent, const QStringList &lnkNames,
                            const QStringList &lnks, const QString &title);

private slots:
    void on_buttonDisplay_clicked();
    void on_buttonCancel_clicked();
    void on_listbox_itemActivated(QListWidgetItem *item);

private:
    Ui::TopicChooser ui;
    QString theLink;
    QStringList links, linkNames;
};

#endif // TOPICCHOOSER_H
