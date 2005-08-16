/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtXMLPatterns module of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation.
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

#include <QUrl>

#include "qabstracturiresolver.h"

QT_BEGIN_NAMESPACE

/*!
  \class QAbstractUriResolver
  \brief The QAbstractUriResolver class is a callback interface for resolving Uniform Resource Identifiers.
  \since 4.4
  \reentrant
  \ingroup xml-tools

  A Uniform Resource Identifier (URI) is a string that uniquely
  identifies a resource. URIs are versatile global identifiers. It is
  often useful to transform a URI that identifies something logical
  into a URI that locates something physical (a URL), or to simply map
  a URI to a different URI. QAbstractUriResolver::resolve() provides
  this functionality.

  For example, one could write a QAbstractUriResolver subclass that
  rewrites library ISBN number URIs as book title URLs, e.g.,
  \e{urn:isbn:0-345-33973-8} would be rewritten as
  \e{file:///books/returnOfTheKing.doc}. Or a QAbstractUriResolver
  subclass could be written for a web browser to let the web browser
  protect the user's private files by mapping incoming requests for
  them to null URIs.

  \sa {http://en.wikipedia.org/wiki/Uniform_Resource_Identifier}
*/

/*!
  Constructs a QAbstractUriResolver with the specified \a parent.
 */
QAbstractUriResolver::QAbstractUriResolver(QObject *parent) : QObject(parent)
{
}

/*!
  Destructor.
 */
QAbstractUriResolver::~QAbstractUriResolver()
{
}

/*!
  \fn QUrl QAbstractUriResolver::resolve(const QUrl &relative, const QUrl &baseURI) const

  Returns the \a relative URI resolved using the \a baseURI.

  The caller guarantees that both \a relative and \a baseURI are
  valid, and that \a baseURI is absolute. \a relative can be relative,
  absolute, or empty.

  The returned QUrl can be a default constructed QUrl. If it is not a
  default constructed QUrl, it will be absolute and valid. If a default
  constructed QUrl is returned, it means the \a relative URI was not
  accepted to be resolved.

  If the reimplemented resolve() function decides it has nothing to do
  about resolving the \a relative URI, it should simply return the \a
  relative URI resolved against the \a baseURI, i.e.:

  \snippet doc/src/snippets/code/src_xmlpatterns_api_qabstracturiresolver.cpp 0

  \sa QUrl::isRelative(), QUrl::isValid()
 */

QT_END_NAMESPACE

