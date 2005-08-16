/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#ifndef PREVIEWFORM_H
#define PREVIEWFORM_H

#include <QDialog>
#include <QList>

class QComboBox;
class QLabel;
class QPushButton;
class QTextCodec;
class QTextEdit;

class PreviewForm : public QDialog
{
    Q_OBJECT

public:
    PreviewForm(QWidget *parent = 0);

    void setCodecList(const QList<QTextCodec *> &list);
    void setEncodedData(const QByteArray &data);
    QString decodedString() const { return decodedStr; }

private slots:
    void updateTextEdit();

private:
    QByteArray encodedData;
    QString decodedStr;

    QComboBox *encodingComboBox;
    QLabel *encodingLabel;
    QTextEdit *textEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif
