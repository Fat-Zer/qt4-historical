/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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

static QFontEngineQPF::TagType tagTypes[QFontEngineQPF::NumTags] = {
    QFontEngineQPF::StringType, // FontName
    QFontEngineQPF::StringType, // FileName
    QFontEngineQPF::UInt32Type, // FileIndex
    QFontEngineQPF::UInt32Type, // FontRevision
    QFontEngineQPF::StringType, // FreeText
    QFontEngineQPF::FixedType,  // Ascent
    QFontEngineQPF::FixedType,  // Descent
    QFontEngineQPF::FixedType,  // Leading
    QFontEngineQPF::FixedType,  // XHeight
    QFontEngineQPF::FixedType,  // AverageCharWidth
    QFontEngineQPF::FixedType,  // MaxCharWidth
    QFontEngineQPF::FixedType,  // LineThickness
    QFontEngineQPF::FixedType,  // MinLeftBearing
    QFontEngineQPF::FixedType,  // MinRightBearing
    QFontEngineQPF::FixedType,  // UnderlinePosition
    QFontEngineQPF::UInt8Type,  // GlyphFormat
    QFontEngineQPF::UInt8Type,  // PixelSize
    QFontEngineQPF::UInt8Type,  // Weight
    QFontEngineQPF::UInt8Type,  // Style
    QFontEngineQPF::StringType, // EndOfHeader
    QFontEngineQPF::BitFieldType// WritingSystems
};


