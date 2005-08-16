/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the linguist application of the Qt Toolkit.
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

#ifndef PHRASEBOOKBOX_H
#define PHRASEBOOKBOX_H

#include "phrase.h"
#include "phrasemodel.h"

#include <qdialog.h>
#include "ui_phrasebookbox.h"

class PhraseBookBox : public QDialog, public Ui::PhraseBookBox
{
    Q_OBJECT
public:
    PhraseBookBox(const QString &filename, const PhraseBook &phraseBook,
        QWidget *parent = 0);

    const PhraseBook &phraseBook() const {return pb;}

protected:
    virtual void keyPressEvent(QKeyEvent *ev);

private slots:
    void newPhrase();
    void removePhrase();
    void save();
    void sourceChanged(const QString &source);
    void targetChanged(const QString &target);
    void definitionChanged(const QString &definition);
    void selectionChanged();

private:
    void sortAndSelectItem(const QModelIndex &index);
    void selectItem(const QModelIndex &index);
    void enableDisable();
    bool blockListSignals;

    QString fn;
    PhraseBook pb;
    PhraseModel *phrMdl;
};

#endif
