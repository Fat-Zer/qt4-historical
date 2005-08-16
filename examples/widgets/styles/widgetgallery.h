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

#ifndef WIDGETGALLERY_H
#define WIDGETGALLERY_H

#include <QDialog>

class QCheckBox;
class QComboBox;
class QDateTimeEdit;
class QDial;
class QGroupBox;
class QLabel;
class QLineEdit;
class QProgressBar;
class QPushButton;
class QRadioButton;
class QScrollBar;
class QSlider;
class QSpinBox;
class QTabWidget;
class QTableWidget;
class QTextEdit;

class WidgetGallery : public QDialog
{
    Q_OBJECT

public:
    WidgetGallery(QWidget *parent = 0);

private slots:
    void changeStyle(const QString &styleName);
    void changePalette();
    void advanceProgressBar();

private:
    void createTopLeftGroupBox();
    void createTopRightGroupBox();
    void createBottomLeftTabWidget();
    void createBottomRightGroupBox();
    void createProgressBar();

    QPalette originalPalette;
 
    QLabel *styleLabel;
    QComboBox *styleComboBox;
    QCheckBox *useStylePaletteCheckBox;
    QCheckBox *disableWidgetsCheckBox;

    QGroupBox *topLeftGroupBox;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QRadioButton *radioButton3;
    QCheckBox *checkBox;

    QGroupBox *topRightGroupBox;
    QPushButton *defaultPushButton;
    QPushButton *togglePushButton;
    QPushButton *flatPushButton;

    QTabWidget *bottomLeftTabWidget;
    QTableWidget *tableWidget;
    QTextEdit *textEdit;

    QGroupBox *bottomRightGroupBox;
    QLineEdit *lineEdit;
    QSpinBox *spinBox;
    QDateTimeEdit *dateTimeEdit;
    QSlider *slider;
    QScrollBar *scrollBar;
    QDial *dial;

    QProgressBar *progressBar;
};

#endif
