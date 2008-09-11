/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

/*
  WebXMLGenerator.h
*/

#ifndef WEBXMLGENERATOR_H
#define WEBXMLGENERATOR_H

#include "codemarker.h"
#include "config.h"
#include "pagegenerator.h"

QT_BEGIN_NAMESPACE

class WebXMLGenerator : public PageGenerator
{
public:
    WebXMLGenerator();
    ~WebXMLGenerator();

    virtual void initializeGenerator(const Config &config);
    virtual void terminateGenerator();
    virtual QString format();
    virtual void generateTree(const Tree *tree, CodeMarker *marker);

protected:
    virtual void startText( const Node *relative, CodeMarker *marker );
    virtual int generateAtom(QXmlStreamWriter &writer, const Atom *atom,
                             const Node *relative, CodeMarker *marker );
    virtual void generateClassLikeNode(const InnerNode *inner, CodeMarker *marker);
    virtual void generateFakeNode(const FakeNode *fake, CodeMarker *marker);
    virtual QString fileExtension(const Node *node);

    virtual const Atom *addAtomElements(QXmlStreamWriter &writer, const Atom *atom,
                                 const Node *relative, CodeMarker *marker);
    virtual void generateIndexSections(QXmlStreamWriter &writer, const Node *node,
                                       CodeMarker *marker);
    virtual void generateInnerNode( const InnerNode *node, CodeMarker *marker );

private:
    const QPair<QString,QString> anchorForNode(const Node *node);
    void findAllClasses(const InnerNode *node);
    void findAllNamespaces(const InnerNode *node);
    const Node *findNode(const Atom *atom, const Node *relative, CodeMarker *marker);
    const Node *findNode(const QString &title, const Node *relative, CodeMarker *marker);
    void generateAnnotatedList(QXmlStreamWriter &writer, const Node *relative,
                               CodeMarker *marker, const QMap<QString,
                               const Node *> &nodeMap);
    void generateFullName(QXmlStreamWriter &writer, const Node *apparentNode,
                          const Node *relative, CodeMarker *marker,
                          const Node *actualNode = 0);
    void generateRelations(QXmlStreamWriter &writer, const Node *node, CodeMarker *marker);
    void generateTableOfContents(QXmlStreamWriter &writer, const Node *node,
                                 Doc::SectioningUnit sectioningUnit,
                                 int numColumns, const Node *relative);
    void startLink(QXmlStreamWriter &writer, const Atom *atom, const Node *node,
                   const Node *relative);
    QString targetType(const Node *node);

    const Tree *tre;
    bool generateIndex;
    bool inLink;
    bool inContents;
    bool inSectionHeading;
    bool inTableHeader;
    int numTableRows;
    bool threeColumnEnumValueTable;
    QMap<QString, QMap<QString, const Node *> > moduleClassMap;
    QMap<QString, QMap<QString, const Node *> > moduleNamespaceMap;
    QMap<QString, const Node *> namespaceIndex;
    QMap<QString, const Node *> serviceClasses;
    QString link;
    QString project;
    QString projectDescription;
    QString projectUrl;
    QStringList sectionNumber;
};

QT_END_NAMESPACE

#endif
