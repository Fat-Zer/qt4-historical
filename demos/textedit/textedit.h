/****************************************************************************
**
** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QMainWindow>
#include <QMap>
#include <QPointer>

class QAction;
class QComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;

class TextEdit : public QMainWindow
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = 0);

protected:
    virtual void closeEvent(QCloseEvent *e);

private:
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    bool load(const QString &f);
    bool maybeSave();
    void setCurrentFileName(const QString &fileName);

private slots:
    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    void filePrintPdf();

    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void textAlign(QAction *a);

    void currentCharFormatChanged(const QTextCharFormat &format);

    void clipboardDataChanged();

private:
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    QAction *actionSave,
        *actionTextBold,
        *actionTextUnderline,
        *actionTextItalic,
        *actionTextColor,
        *actionAlignLeft,
        *actionAlignCenter,
        *actionAlignRight,
        *actionAlignJustify,
        *actionUndo,
        *actionRedo,
        *actionCut,
        *actionCopy,
        *actionPaste;

    QComboBox *comboStyle,
              *comboFont,
              *comboSize;

    QToolBar *tb;
    QString fileName;
    QTextEdit *textEdit;
};

#endif
