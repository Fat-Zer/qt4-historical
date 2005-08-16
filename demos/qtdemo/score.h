/****************************************************************************
**
** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
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
** Trolltech ASA (c) 2007
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef SCORE_H
#define SCORE_H

#include <QList>
#include <QHash>
#include "demoitemanimation.h"

typedef QList<DemoItemAnimation *> Movie;
typedef QHash<QString, Movie*> MovieIndex;

class PlayListMember
{
public:
    PlayListMember(Movie *movie, int runMode) : movie(movie), runMode(runMode){};
    Movie *movie;
    int runMode;
};
typedef QList<PlayListMember> PlayList;

class Score
{
public:
    enum LOCK_MODE {LOCK_ITEMS, UNLOCK_ITEMS, SKIP_LOCK};
    enum RUN_MODE {FROM_CURRENT, FROM_START, NEW_ANIMATION_ONLY};
    
    Score();
    virtual ~Score();
    
    void playMovie(const QString &indexName, RUN_MODE runMode = FROM_START, LOCK_MODE lockMode = SKIP_LOCK);
    void insertMovie(const QString &indexName, Movie *movie);
    void queueMovie(const QString &indexName, RUN_MODE runMode = FROM_START, LOCK_MODE lockMode = SKIP_LOCK);
    void playQue();

    MovieIndex index;
    PlayList playList;
    
private:
    void prepare(Movie *movie, LOCK_MODE lockMode);
    void play(Movie *movie, RUN_MODE runMode);  
};

#endif // SCORE_H

