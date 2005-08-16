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

#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <QtGui>
#include <QtXml>
#include <QtAssistant/QAssistantClient>
#include "score.h"
#include "textbutton.h"
#include "mainwindow.h"
#include "itemcircleanimation.h"

typedef QHash<QString, QString> StringHash;
typedef QHash<QString, StringHash> HashHash;

class MenuManager : public QObject
{
    Q_OBJECT
    
public:
    enum BUTTON_TYPE {ROOT, MENU1, MENU2, LAUNCH, DOCUMENTATION, QUIT, FULLSCREEN};
    
    // singleton pattern:
    static MenuManager *instance();
    virtual ~MenuManager();
    
    void init(MainWindow *window);
    void itemSelected(int userCode, const QString &menuName = "");
    
    HashHash info;
    ItemCircleAnimation *ticker;
    MainWindow *window;
    
private slots:
    void exampleFinished();
    void exampleError(QProcess::ProcessError error);
    
private:
    // singleton pattern:
    MenuManager();
    static MenuManager *pInstance;
    
    void readXmlDocument();
    void getDocumentationDir();
    void readInfoAboutExample(const QDomElement &example);
    void createLeftMenu1(const QDomElement &el);
    void createRightMenu1(const QDomElement &el);
    void createLeafMenu(const QDomElement &el);
    void createInfo(DemoItem *item, const QString &name);
    void createTicker();
    void launchExample(const QString &uniqueName);
    
    QString resolveExecutable(const QDomElement &example);
    QString resolveDocFile(const QDomElement &example);
    QString resolveImgFile(const QDomElement &example);
    
    QDomDocument *contentsDoc;
    QAssistantClient *assistant;
    Score *score;
    QString currentMenu;
    QString currentExample;
    QDir docDir;
    QDir imgDir;
};

#endif // MENU_MANAGER_H

