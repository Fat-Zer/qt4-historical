/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the virtual framebuffer of the Qt Toolkit.
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

#include <qmainwindow.h>

class QVFbView;
class QVFbRateDialog;
class QPopupMenu;
class QMenu;
class QAction;
class Config;
class QScrollArea;
class Skin;

class QVFb: public QMainWindow
{
    Q_OBJECT
public:
    QVFb( int display_id, int w, int h, int d, const QString &skin, QWidget *parent = 0,
		const char *name = 0, Qt::WFlags = 0 );
    ~QVFb();

    void enableCursor( bool e );
    QMenu *createPopupMenu();

protected slots:
    void saveImage();
    void toggleAnimation();
    void toggleCursor();
    void changeRate();
    void about();
    void aboutQt();

    void configure();

    void setZoom(double);
    void setZoom1();
    void setZoom2();
    void setZoom3();
    void setZoom4();
    void setZoomHalf();

protected:
    void createMenuBar();

private:
    void init( int display_id, int w, int h, int d, const QString &skin );
    QAction *newAction(const char *menuName, const char *shortkey, const char *slot);
    void createActions();

    QVFbView *view;
    QScrollArea *scroller;
    Skin *skin;
    QVFbRateDialog *rateDlg;
    Config* config;
    QString currentSkin;

    enum FBActs { ConfigAct,
                  QuitAct,
                  AboutAct,
                  AboutQtAct,
//                  HelpAct,
//                  FileAct,
                  SaveAct,
                  AnimationAct,
                  CursorAct,
//                  ViewAct,
                  RefreshAct,
                  Zoom1Act,
                  Zoom2Act,
                  Zoom3Act,
                  Zoom4Act,
                  Zoom05Act,
                  NCountAct
    };

    QAction *actions[NCountAct];

private slots:
    void resetGamma();
    void setGamma400(int n);
    void setR400(int n);
    void setG400(int n);
    void setB400(int n);
    void updateGammaLabels();
};

