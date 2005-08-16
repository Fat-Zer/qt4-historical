/****************************************************************************
**
** Copyright (C) 2005-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#ifndef MULTIPAGEWIDGET_H
#define MULTIPAGEWIDGET_H

#include <QWidget>

class QComboBox;
class QStackedWidget;
class QVBoxLayout;

class MultiPageWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QString pageTitle READ pageTitle WRITE setPageTitle STORED false)

public:
    MultiPageWidget(QWidget *parent = 0);

    QSize sizeHint() const;

    void addPage(QWidget *page);
    void removePage(int index);
    int count() const;
    int currentIndex() const;
    void insertPage(int index, QWidget *page);
    QWidget *widget(int index);

    QString pageTitle() const;
    void setPageTitle(QString const &newTitle);

public slots:
    void setCurrentIndex(int index);

signals:
    void currentIndexChanged(int index);
    void pageTitleChanged(const QString &title);

private:
    QStackedWidget *stackWidget;
    QComboBox *comboBox;
    QVBoxLayout *layout;
};

#endif
