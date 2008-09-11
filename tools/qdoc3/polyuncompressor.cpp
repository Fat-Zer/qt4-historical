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

#include "command.h"
#include "polyuncompressor.h"

QT_BEGIN_NAMESPACE

/*!
  \class PolyUncompressor
  
  \brief The PolyUncompressor class is a class for uncompressing
  compressed files.

  This subclass of Uncompressor contains a parameterized
  command for doing the uncompression

  It has an uncompressFile() function you call to do the
  actual uncompression.
 */

/*!
  The constructor takes the list of filename \a extensions,
  which it passes to the base class, and the \a commandFormat,
  which it stores locally. The \a commandFormat is a command
  template string.
 */
PolyUncompressor::PolyUncompressor( const QStringList& extensions,
				    const QString& commandFormat )
    : Uncompressor( extensions ), cmd( commandFormat )
{
}

/*!
  The destructor doesn't have to do anything.
 */
PolyUncompressor::~PolyUncompressor()
{
}

/*!
  From \a filePath, derive a file path for the uncompressed
  file and return it. If it can't figure out what the file
  path should be, it just concatenates ".out" to the
  \a filePath and returns that.
 */
QString PolyUncompressor::uncompressedFilePath( const QString& filePath )
{
    QStringList::ConstIterator e = fileExtensions().begin();
    while ( e != fileExtensions().end() ) {
	QString dotExt = "." + *e;
	if ( filePath.endsWith(dotExt) )
	    return filePath.left( filePath.length() - dotExt.length() );
	++e;
    }
    return filePath + ".out"; // doesn't really matter
}

/*!
  Call this function to do the actual uncompressing. It calls
  the executeCommand() function to do the work. That's all it does.
 */
void PolyUncompressor::uncompressFile( const Location& location,
				       const QString& filePath,
				       const QString& outputFilePath )
{
    executeCommand( location, cmd,
		    QStringList() << filePath << outputFilePath );
}

QT_END_NAMESPACE
