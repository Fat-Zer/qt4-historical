/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
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
