/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QTEXTBROWSER_H
#define QTEXTBROWSER_H

#include "QtGui/qtextedit.h"
#include <QtCore/qurl.h>

class QTextBrowserPrivate;

class Q_GUI_EXPORT QTextBrowser : public QTextEdit
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource)
    Q_OVERRIDE(bool modified SCRIPTABLE false)
    Q_OVERRIDE(bool readOnly DESIGNABLE false SCRIPTABLE false)
    Q_OVERRIDE(bool undoRedoEnabled DESIGNABLE false SCRIPTABLE false)
    Q_PROPERTY(QStringList searchPaths READ searchPaths WRITE setSearchPaths)

public:
    explicit QTextBrowser(QWidget* parent = 0);
    virtual ~QTextBrowser();

    QUrl source() const;

    QStringList searchPaths() const;
    void setSearchPaths(const QStringList &paths);

    virtual QVariant loadResource(int type, const QUrl &name);

public slots:
    virtual void setSource(const QUrl &name);
    virtual void backward();
    virtual void forward();
    virtual void home();
    virtual void reload();

signals:
    void backwardAvailable(bool);
    void forwardAvailable(bool);
    void sourceChanged(const QUrl &);
    void highlighted(const QUrl &);
    void highlighted(const QString &);
    void anchorClicked(const QUrl &);

protected:
    virtual void keyPressEvent(QKeyEvent *ev);
    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void focusOutEvent(QFocusEvent *ev);
    virtual bool focusNextPrevChild(bool next);
    virtual void paintEvent(QPaintEvent *e);

#if defined(QT3_SUPPORT)
public:
    QT3_SUPPORT_CONSTRUCTOR QTextBrowser(QWidget *parent, const char *name);
#endif

private:
    Q_DISABLE_COPY(QTextBrowser)
    Q_DECLARE_PRIVATE(QTextBrowser)
    Q_PRIVATE_SLOT(d_func(), void documentModified())
};

#endif // QTEXTBROWSER_H
