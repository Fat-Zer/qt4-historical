/****************************************************************************
**
** Copyright (C) 2006-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
#include <QPrinter>
#include <QList>
#include <QStringList>
#include "ui_previewdialogbase.h"
#include "previewlabel.h"

class QTreeWidgetItem;

typedef QList<QTreeWidgetItem *> StyleItems;

Q_DECLARE_METATYPE(StyleItems);

class PreviewDialog : public QDialog, private Ui::PreviewDialogBase
{
    Q_OBJECT

public:
    PreviewDialog(QPrinter &printer, QWidget *parent);
    enum { SmallPreviewLength = 200, LargePreviewLength = 400 };

    bool isSelected(int index);

signals:
    void pageRequested(int index, QPainter &painter, QPrinter &printer);

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void accept();
    void addPage();
    void on_pageList_currentItemChanged();
    void on_paperSizeCombo_activated(int index);
    void on_paperOrientationCombo_activated(int index);
    void reject();
    void setNumberOfPages(int count);

private:
    void paintItem(QTreeWidgetItem *item, int index);
    void paintPreview(QPixmap &pixmap, int index);
    void setupComboBoxes();

    PreviewLabel *previewLabel;
    QPrinter &printer;
    bool canceled;
    int currentPage;
    int pageCount;
};

#endif
