/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
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

#ifndef RICHTEXTEDITOR_H
#define RICHTEXTEDITOR_H

#include <QtGui/QTextEdit>
#include <QtGui/QDialog>
#include "shared_global_p.h"

class QToolBar;

class QT_SHARED_EXPORT RichTextEditor : public QTextEdit
{
    Q_OBJECT
public:
    RichTextEditor(QWidget *parent = 0);
    void setDefaultFont(const QFont &font);

    QToolBar *createToolBar(QWidget *parent = 0);

public slots:
    void setFontBold(bool b);
    void setFontPointSize(double);
    void setText(const QString &text);
    QString text(Qt::TextFormat format) const;

signals:
    void textChanged();

private:
    Qt::TextFormat detectFormat() const;
};

class QT_SHARED_EXPORT RichTextEditorDialog : public QDialog
{
    Q_OBJECT
public:
    RichTextEditorDialog(QWidget *parent = 0);
    RichTextEditor *editor();

private:
    RichTextEditor *m_editor;
};

#endif // RITCHTEXTEDITOR_H
