/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the $MODULE$ of the Qt Toolkit.
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

#ifndef QSCRIPTNODEPOOL_P_H
#define QSCRIPTNODEPOOL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/QHash>
#include <QtCore/QString>

#include "qscriptmemorypool_p.h"

namespace QScript {

namespace AST {
class Node;
} // namespace AST

class Code;
class CompilationUnit;

template <typename NodeType>
inline NodeType *makeAstNode(MemoryPool *storage)
{
    NodeType *node = new (storage->allocate(sizeof(NodeType))) NodeType();
    return node;
}

template <typename NodeType, typename Arg1>
inline NodeType *makeAstNode(MemoryPool *storage, Arg1 arg1)
{
    NodeType *node = new (storage->allocate(sizeof(NodeType))) NodeType(arg1);
    return node;
}

template <typename NodeType, typename Arg1, typename Arg2>
inline NodeType *makeAstNode(MemoryPool *storage, Arg1 arg1, Arg2 arg2)
{
    NodeType *node = new (storage->allocate(sizeof(NodeType))) NodeType(arg1, arg2);
    return node;
}

template <typename NodeType, typename Arg1, typename Arg2, typename Arg3>
inline NodeType *makeAstNode(MemoryPool *storage, Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
    NodeType *node = new (storage->allocate(sizeof(NodeType))) NodeType(arg1, arg2, arg3);
    return node;
}

template <typename NodeType, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
inline NodeType *makeAstNode(MemoryPool *storage, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
{
    NodeType *node = new (storage->allocate(sizeof(NodeType))) NodeType(arg1, arg2, arg3, arg4);
    return node;
}

class NodePool : public MemoryPool
{
public:
    NodePool(const QString &fileName) : m_fileName(fileName) { }
    virtual ~NodePool();

    Code *createCompiledCode(AST::Node *node, CompilationUnit &compilation);

    inline QString fileName() const { return m_fileName; }

private:
    QHash<AST::Node*, Code*> m_codeCache;
    QString m_fileName;

private:
    Q_DISABLE_COPY(NodePool)
};

} // namespace QScript

#endif

