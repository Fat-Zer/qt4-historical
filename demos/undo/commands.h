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

#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include "document.h"

class AddShapeCommand : public QUndoCommand
{
public:
    AddShapeCommand(Document *doc, const Shape &shape, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    Document *m_doc;
    Shape m_shape;
    QString m_shapeName;
};

class RemoveShapeCommand : public QUndoCommand
{
public:
    RemoveShapeCommand(Document *doc, const QString &shapeName, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    Document *m_doc;
    Shape m_shape;
    QString m_shapeName;
};

class SetShapeColorCommand : public QUndoCommand
{
public:
    SetShapeColorCommand(Document *doc, const QString &shapeName, const QColor &color,
                            QUndoCommand *parent = 0);

    void undo();
    void redo();

    bool mergeWith(const QUndoCommand *command);
    int id() const;

private:
    Document *m_doc;
    QString m_shapeName;
    QColor m_oldColor;
    QColor m_newColor;
};

class SetShapeRectCommand : public QUndoCommand
{
public:
    SetShapeRectCommand(Document *doc, const QString &shapeName, const QRect &rect,
                            QUndoCommand *parent = 0);

    void undo();
    void redo();

    bool mergeWith(const QUndoCommand *command);
    int id() const;

private:
    Document *m_doc;
    QString m_shapeName;
    QRect m_oldRect;
    QRect m_newRect;
};

#endif // COMMANDS_H
