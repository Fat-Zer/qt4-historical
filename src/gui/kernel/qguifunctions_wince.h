/****************************************************************************
**
** Copyright (C) 2006-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
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
#ifndef QGUIFUNCTIONS_WCE_H
#define QGUIFUNCTIONS_WCE_H
#ifdef Q_OS_WINCE
#include <aygshell.h>
#include <QtCore/qfunctions_wince.h>
#define UNDER_NT
#include <wingdi.h>

#ifdef QT_BUILD_GUI_LIB
QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE
QT_MODULE(Gui)
QT_END_NAMESPACE
QT_END_HEADER
#endif

// application defines
#define SPI_SETNONCLIENTMETRICS 72
#define SPI_SETICONTITLELOGFONT 0x0022
#define WM_ACTIVATEAPP 0x001c
#define SW_PARENTCLOSING    1
#define SW_OTHERMAXIMIZED   2
#define SW_PARENTOPENING    3
#define SW_OTHERRESTORED    4
#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))

// drag n drop
#ifndef CFSTR_PERFORMEDDROPEFFECT
#define CFSTR_PERFORMEDDROPEFFECT TEXT("Performed DropEffect")
#endif
int GetDIBits(HDC, HBITMAP, uint, uint, void*, LPBITMAPINFO, uint);

// QWidget
#define SW_SHOWMINIMIZED SW_MINIMIZE

// QPaintEngine
bool TextOutW(HDC, int, int, LPWSTR, UINT);

// QRegion
#define ALTERNATE 0
#define WINDING 1

// QFontEngine
typedef struct _FIXED { 
  WORD  fract; 
  short value; 
} FIXED;

typedef struct tagPOINTFX { 
  FIXED x; 
  FIXED y; 
} POINTFX;

typedef struct _MAT2 { 
  FIXED eM11; 
  FIXED eM12; 
  FIXED eM21; 
  FIXED eM22; 
} MAT2;

typedef struct _GLYPHMETRICS {
    UINT    gmBlackBoxX;
    UINT    gmBlackBoxY;
    POINT   gmptGlyphOrigin;
    short   gmCellIncX;
    short   gmCellIncY;
} GLYPHMETRICS;

typedef struct tagTTPOLYGONHEADER
{
    DWORD   cb;
    DWORD   dwType;
    POINTFX pfxStart;
} TTPOLYGONHEADER;

typedef struct tagTTPOLYCURVE
{
    WORD    wType;
    WORD    cpfx;
    POINTFX apfx[1];
} TTPOLYCURVE;

#define GGO_NATIVE 2
#define GGO_GLYPH_INDEX 0x0080
#define TT_PRIM_LINE 1
#define TT_PRIM_QSPLINE 2
#define TT_PRIM_CSPLINE 3
#define ANSI_VAR_FONT 12

HINSTANCE ShellExecute(HWND hwnd, LPCTSTR operation, LPCTSTR file, LPCTSTR params, LPCTSTR dir, int showCmd);


// Clipboard --------------------------------------------------------
#define WM_CHANGECBCHAIN	1
#define WM_DRAWCLIPBOARD	2

BOOL ChangeClipboardChain(
    HWND hWndRemove,  // handle to window to remove
    HWND hWndNewNext  // handle to next window
);

HWND SetClipboardViewer(
    HWND hWndNewViewer   // handle to clipboard viewer window
);

// Graphics ---------------------------------------------------------
COLORREF PALETTEINDEX( WORD wPaletteIndex );
BOOL TextOut( HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString );

#endif // Q_OS_WINCE
#endif // QGUIFUNCTIONS_WCE_H
