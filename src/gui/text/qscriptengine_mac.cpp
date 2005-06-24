/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the text module of the Qt Toolkit.
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

const q_scriptEngine qt_scriptEngines[] = {
    // Common
    { basic_shape, basic_attributes },
    // Hebrew
    { basic_shape, basic_attributes },
    // Arabic
    { arabic_shape, arabic_attributes },
    // Syriac
    { basic_shape, basic_attributes },
    // Thaana
    { basic_shape, basic_attributes },
    // Devanagari
    { basic_shape, basic_attributes },
    // Bengali
    { basic_shape, basic_attributes },
    // Gurmukhi
    { basic_shape, basic_attributes },
    // Gujarati
    { basic_shape, basic_attributes },
    // Oriya
    { basic_shape, basic_attributes },
    // Tamil
    { basic_shape, basic_attributes },
    // Telugu
    { basic_shape, basic_attributes },
    // Kannada
    { basic_shape, basic_attributes },
    // Malayalam
    { basic_shape, basic_attributes },
    // Sinhala
    { basic_shape, basic_attributes },
    // Thai
    { basic_shape, basic_attributes },
    // Lao
    { basic_shape, basic_attributes },
    // Tibetan
    { basic_shape, basic_attributes },
    // Myanmar
    { basic_shape, basic_attributes },
    // Hangul
    { basic_shape, basic_attributes },
    // Khmer
    { basic_shape, basic_attributes }

#if 0
    // ### What about this one?
    // Unicode
    { unicode_shape, basic_attributes }
#endif

};
