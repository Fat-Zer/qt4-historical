/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#ifndef CONTROLLERWINDOW_H
#define CONTROLLERWINDOW_H

#include <QWidget>

#include "previewwindow.h"

class QCheckBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QRadioButton;

class ControllerWindow : public QWidget
{
    Q_OBJECT

public:
    ControllerWindow();

private slots:
    void updatePreview();

private:
    void createTypeGroupBox();
    void createHintsGroupBox();
    QCheckBox *createCheckBox(const QString &text);
    QRadioButton *createRadioButton(const QString &text);

    PreviewWindow *previewWindow;

    QGroupBox *typeGroupBox;
    QGroupBox *hintsGroupBox;
    QPushButton *quitButton;

    QRadioButton *windowRadioButton;
    QRadioButton *dialogRadioButton;
    QRadioButton *sheetRadioButton;
    QRadioButton *drawerRadioButton;
    QRadioButton *popupRadioButton;
    QRadioButton *toolRadioButton;
    QRadioButton *toolTipRadioButton;
    QRadioButton *splashScreenRadioButton;

    QCheckBox *msWindowsFixedSizeDialogCheckBox;
    QCheckBox *x11BypassWindowManagerCheckBox;
    QCheckBox *framelessWindowCheckBox;
    QCheckBox *windowTitleCheckBox;
    QCheckBox *windowSystemMenuCheckBox;
    QCheckBox *windowMinimizeButtonCheckBox;
    QCheckBox *windowMaximizeButtonCheckBox;
    QCheckBox *windowContextHelpButtonCheckBox;
    QCheckBox *windowShadeButtonCheckBox;
    QCheckBox *windowStaysOnTopCheckBox;
};

#endif
