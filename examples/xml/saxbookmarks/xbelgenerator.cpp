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

#include <QtGui>

#include "xbelgenerator.h"

XbelGenerator::XbelGenerator(QTreeWidget *treeWidget)
    : treeWidget(treeWidget)
{
}

bool XbelGenerator::write(QIODevice *device)
{
    out.setDevice(device);
    out.setCodec("UTF-8");
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        << "<!DOCTYPE xbel>\n"
        << "<xbel version=\"1.0\">\n";

    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
        generateItem(treeWidget->topLevelItem(i), 1);

    out << "</xbel>\n";
    return true;
}

QString XbelGenerator::indent(int depth)
{
    const int IndentSize = 4;
    return QString(IndentSize * depth, ' ');
}

QString XbelGenerator::escapedText(const QString &str)
{
    QString result = str;
    result.replace("&", "&amp;");
    result.replace("<", "&lt;");
    result.replace(">", "&gt;");
    return result;
}

QString XbelGenerator::escapedAttribute(const QString &str)
{
    QString result = escapedText(str);
    result.replace("\"", "&quot;");
    result.prepend("\"");
    result.append("\"");
    return result;
}

void XbelGenerator::generateItem(QTreeWidgetItem *item, int depth)
{
    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == "folder") {
        bool folded = !treeWidget->isItemExpanded(item);
        out << indent(depth) << "<folder folded=\"" << (folded ? "yes" : "no")
                             << "\">\n"
            << indent(depth + 1) << "<title>" << escapedText(item->text(0))
                                 << "</title>\n";

        for (int i = 0; i < item->childCount(); ++i)
            generateItem(item->child(i), depth + 1);

        out << indent(depth) << "</folder>\n";
    } else if (tagName == "bookmark") {
        out << indent(depth) << "<bookmark";
        if (!item->text(1).isEmpty())
            out << " href=" << escapedAttribute(item->text(1));
        out << ">\n"
            << indent(depth + 1) << "<title>" << escapedText(item->text(0))
                                 << "</title>\n"
            << indent(depth) << "</bookmark>\n";
    } else if (tagName == "separator") {
        out << indent(depth) << "<separator/>\n";
    }
}
