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

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QDir>
#include <QDomNode>
#include <QImage>
#include <QMap>
#include <QMainWindow>
#include <QString>
#include <QStringList>

class DisplayShape;
class DisplayWidget;
class QAssistantClient;
class QProcess;

class Launcher : public QMainWindow
{
    Q_OBJECT

public:
    Launcher(QWidget *parent = 0);
    bool setup();

public slots:
    void enableLaunching();
    void executeAction(const QString &action);
    void launchExample(const QString &example);
    void showCategories();
    void showExampleDocumentation(const QString &example);
    void showExamples(const QString &category);
    void showExampleSummary(const QString &example);
    void showParentPage();
    void updateExampleSummary();

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);

signals:
    void showPage();
    void windowResized();

private slots:
    void toggleFullScreen();
    void redisplayWindow();
    void resizeWindow();

private:
    QString readExampleDescription(const QDomNode &parentNode) const;
    void findDescriptionAndImages(const QString &exampleName,
                                  const QString &docName);
    QString findExecutable(const QDir &dir) const;
    void newPage();
    void readCategoryDescription(const QDir &categoryDir,
                                 const QString &categoryName);
    int readInfo(const QString &resource, const QDir &dir);

    bool inFullScreenResize;
    int maximumLabels;
    int slideshowFrame;
    qreal fontRatio;
    DisplayShape *currentFrame;
    DisplayWidget *display;
    QAssistantClient *assistant;
    QDir documentationDir;
    QDir imagesDir;
    QDir demosDir;
    QDir examplesDir;
    QFont buttonFont;
    QFont textFont;
    QFont titleFont;
    QImage qtLogo;
    QImage trolltechLogo;
    QMap<QString,QColor> categoryColors;
    QMap<QString,QColor> exampleColors;
    QMap<QProcess*,QString> runningProcesses;
    QMap<QString,QString> categoryDescriptions;
    QMap<QString,QString> exampleDescriptions;
    QMap<QString,QString> documentPaths;
    QMap<QString,QPair<QString,QString> > examplePaths;
    QMap<QString,QStringList> examples;
    QMap<QString,QStringList> imagePaths;
    QString currentCategory;
    QString currentExample;
    QStringList runningExamples;
    QStringList categories;
    QTimer *resizeTimer;
    QTimer *slideshowTimer;
};

#endif
