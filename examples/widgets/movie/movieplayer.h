/****************************************************************************
**
** Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
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

#ifndef MOVIEPLAYER_H
#define MOVIEPLAYER_H

#include <QWidget>

class QCheckBox;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QSlider;
class QToolButton;
class QVBoxLayout;

class MoviePlayer : public QWidget
{
    Q_OBJECT

public:
    MoviePlayer(QWidget *parent = 0);

public slots:
    void browse();
    void start();
    void stop();
    void goToFrame(int frame);
    void scaleMovie();

private:
    QLabel *movieScreen;
    QString currentMovieDirectory;

    void createButtons();
    void createCheckBox();
    void createSliders();

    QToolButton *browseButton;
    QToolButton *playButton;
    QToolButton *quitButton;
    QToolButton *stopButton;
    QCheckBox *scaleMovieCheckbox;
    QSlider *frameSlider;
    QSlider *speedSlider;
    QLabel *frameLabel;
    QLabel *speedLabel;

    QHBoxLayout *buttonsLayout;
    QGridLayout *slidersLayout;
    QVBoxLayout *mainLayout;
};

#endif
