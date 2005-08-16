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
#include "qguifunctions_wince.h"
#include <shellapi.h>
#include <QtCore/qlibrary.h>

QT_USE_NAMESPACE

struct AygSHINITDLGINFO
{
    DWORD dwMask;
    HWND  hDlg;
    DWORD dwFlags;
};
#ifndef SHIDIF_CANCELBUTTON
#define SHIDIF_CANCELBUTTON 0x0080
#endif

typedef BOOL (*AygInitDialog)(AygSHINITDLGINFO*);
typedef BOOL (*AygFullScreen)(HWND, DWORD);

static AygInitDialog ptrAygInitDialog = 0;
static AygFullScreen ptrAygFullScreen = 0;
static bool aygResolved = false;

static void resolveAygLibs()
{
    if (!aygResolved) {
        aygResolved = true;
        QLibrary ayglib(QLatin1String("aygshell"));
        if (!ayglib.load())
            return;
        ptrAygInitDialog = (AygInitDialog) ayglib.resolve("SHInitDialog");
        ptrAygFullScreen = (AygFullScreen) ayglib.resolve("SHFullScreen");
    }
}

struct DIBINFO : public BITMAPINFO 
{ 
    RGBQUAD arColors[255]; 

    operator LPBITMAPINFO() { return (LPBITMAPINFO) this; } 
    operator LPBITMAPINFOHEADER() { return &bmiHeader; } 
    RGBQUAD* ColorTable() { return bmiColors; } 
};

int GetDIBits(HDC /*hdc*/ , HBITMAP hSourceBitmap, uint, uint, LPVOID lpvBits, LPBITMAPINFO, uint)
{
    if (!lpvBits) {
        qWarning("::GetDIBits(), lpvBits NULL");
        return 0;
    }
    BITMAP bm; 
    GetObject(hSourceBitmap, sizeof(BITMAP), &bm);
    bm.bmHeight = abs(bm.bmHeight);

    HBITMAP hTargetBitmap; 
    void *pixels;

    BITMAPINFO dibInfo;
    memset(&dibInfo, 0, sizeof(dibInfo));
    dibInfo.bmiHeader.biBitCount = 32;
    dibInfo.bmiHeader.biClrImportant = 0;
    dibInfo.bmiHeader.biClrUsed = 0;
    dibInfo.bmiHeader.biCompression = BI_RGB;;
    dibInfo.bmiHeader.biHeight = -bm.bmHeight;
    dibInfo.bmiHeader.biWidth = bm.bmWidth;
    dibInfo.bmiHeader.biPlanes = 1;
    dibInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    dibInfo.bmiHeader.biSizeImage = bm.bmWidth * bm.bmHeight * 4;

    HDC displayDC = GetDC(NULL);
    if (!displayDC) {
        qWarning("::GetDIBits(), failed to GetDC");
        return 0;
    }

    int ret = bm.bmHeight;

    hTargetBitmap = CreateDIBSection(displayDC, (const BITMAPINFO*) &dibInfo, DIB_RGB_COLORS,
                                    (void**)&pixels, NULL, 0);
    if (!hTargetBitmap) {
        qWarning("::GetDIBits(), failed to CreateDIBSection");
        return 0;
    }

    HDC hdcSrc = CreateCompatibleDC(displayDC);
    HDC hdcDst = CreateCompatibleDC(displayDC);

    if (!(hdcDst && hdcSrc)) {
        qWarning("::GetDIBits(), failed to CreateCompatibleDC");
        ret = 0;
    }

    HBITMAP hOldBitmap1 = (HBITMAP) SelectObject(hdcSrc, hSourceBitmap);
    HBITMAP hOldBitmap2 = (HBITMAP) SelectObject(hdcDst, hTargetBitmap);

    if (!(hOldBitmap1 && hOldBitmap2)) {
        qWarning("::GetDIBits(), failed to SelectObject for bitmaps");
        ret = 0;
    }

    if (!BitBlt(hdcDst, 0, 0, bm.bmWidth, bm.bmHeight, hdcSrc, 0, 0, SRCCOPY)) {
        qWarning("::GetDIBits(), BitBlt failed");
        ret = 0;
    }

    SelectObject(hdcSrc, hOldBitmap1);
    SelectObject(hdcDst, hOldBitmap2);

    DeleteDC(hdcSrc);
    DeleteDC(hdcDst);

    ReleaseDC(NULL, displayDC);

    memcpy(lpvBits, pixels, dibInfo.bmiHeader.biSizeImage);

    DeleteObject(hTargetBitmap);
    return ret;
}

bool TextOutW(HDC hdc, int x, int y, LPWSTR lpString, UINT c)
{
    return ExtTextOutW(hdc, x, y, 0, NULL, lpString, c, NULL);
}


HINSTANCE ShellExecute(HWND hwnd, LPCTSTR, LPCTSTR file, LPCTSTR params, LPCTSTR dir, int showCmd)
{
    SHELLEXECUTEINFO info;
    info.hwnd = hwnd;
    info.lpVerb = L"Open";
    info.lpFile = file;
    info.lpParameters = params;
    info.lpDirectory = dir;
    info.nShow = showCmd;
    info.cbSize = sizeof(info);
    ShellExecuteEx(&info);
    return info.hInstApp;
}

// Clipboard --------------------------------------------------------
BOOL ChangeClipboardChain( HWND /*hWndRemove*/, HWND /*hWndNewNext*/ ) 
{ 
    return FALSE; 
}

HWND SetClipboardViewer( HWND /*hWndNewViewer*/ )
{ 
    return NULL; 
}


// Graphics ---------------------------------------------------------
COLORREF PALETTEINDEX( WORD /*wPaletteIndex*/) 
{
    return 0;
}

BOOL TextOut( HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString ) 
{
    return ExtTextOut( hdc, nXStart, nYStart - 16, 0, NULL, lpString, cbString, NULL );
}

// Internal Qt -----------------------------------------------------
bool qt_wince_is_platform(const QString &platformString) {
    TCHAR tszPlatform[64];
    if (SystemParametersInfo(SPI_GETPLATFORMTYPE,
                             sizeof(tszPlatform)/sizeof(*tszPlatform),tszPlatform,0))
      if (0 == _tcsicmp(reinterpret_cast<const wchar_t *> (platformString.utf16()), tszPlatform))
            return true;
    return false;
}

bool qt_wince_is_pocket_pc() {
    return qt_wince_is_platform(QString::fromLatin1("PocketPC"));
}

bool qt_wince_is_smartphone() {
       return qt_wince_is_platform(QString::fromLatin1("Smartphone"));
}
bool qt_wince_is_mobile() {
     return (qt_wince_is_smartphone() || qt_wince_is_pocket_pc());
}

bool qt_wince_is_high_dpi() {
    if (!qt_wince_is_pocket_pc()) 
        return false;
    HDC deviceContext = GetDC(0);
    int dpi = GetDeviceCaps(deviceContext, LOGPIXELSX);
    ReleaseDC(0, deviceContext);
    if ((dpi < 1000) && (dpi > 0))
        return dpi > 96;
    else
        return false;
}

void qt_wince_maximize(QWidget *widget)
{
    HWND hwnd = widget->winId();
    if (qt_wince_is_mobile()) {
        AygSHINITDLGINFO shidi;
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.hDlg = hwnd;
        shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
        if (widget->windowFlags() & Qt::WindowCancelButtonHint)
            shidi.dwFlags |= SHIDIF_CANCELBUTTON;
        if (widget->windowFlags() & Qt::WindowOkButtonHint)
            shidi.dwFlags |= SHIDIF_DONEBUTTON;
        resolveAygLibs();
        if (ptrAygInitDialog)
            ptrAygInitDialog(&shidi);
    } else {
        RECT r;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
        MoveWindow(hwnd, r.top, r.left, r.right - r.left, r.bottom - r.top, true);
        SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong (hwnd, GWL_EXSTYLE) | WS_EX_NODRAG);
    }
}

void qt_wince_minimize(HWND hwnd) {

    uint exstyle = GetWindowLongW(hwnd, GWL_EXSTYLE);
    uint style = GetWindowLongW(hwnd, GWL_STYLE);
    RECT rect;
    RECT crect = {0,0,0,0};
    GetWindowRect(hwnd, &rect);
    AdjustWindowRectEx(&crect, style & ~WS_OVERLAPPED, FALSE, exstyle);
    MoveWindow(hwnd, rect.left - crect.left, rect.top - crect.top, 0, 0, true);
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong (hwnd, GWL_EXSTYLE) | WS_EX_NODRAG);
    ShowWindow(hwnd, SW_HIDE);
}


void qt_wince_hide_taskbar(HWND hwnd) {
    if (ptrAygFullScreen)
        ptrAygFullScreen(hwnd, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON | SHFS_HIDESTARTICON);
}

void qt_wince_full_screen(HWND hwnd, bool fullScreen, UINT swpf) {
    resolveAygLibs();
    if (fullScreen) {
        QRect r = qApp->desktop()->screenGeometry(QWidget::find(hwnd));
        SetWindowPos(hwnd, HWND_TOP, r.left(), r.top(), r.width(), r.height(), swpf);
        if (ptrAygFullScreen)
            ptrAygFullScreen(hwnd, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON | SHFS_HIDESTARTICON);
        if (!qt_wince_is_mobile()) {
            HWND handle = FindWindow(L"HHTaskBar", L"");
            if (handle) {
                ShowWindow(handle, 0);
                EnableWindow(handle, false);
            }
        }
    } else {
        if (ptrAygFullScreen)
            ptrAygFullScreen(hwnd, SHFS_SHOWTASKBAR | SHFS_SHOWSIPBUTTON | SHFS_SHOWSTARTICON);
        SetWindowPos(hwnd, 0, 0, 0, 0, 0, swpf);
        if (!qt_wince_is_mobile()) {
            HWND handle = FindWindow(L"HHTaskBar", L"");
            if (handle) {
                ShowWindow(handle, 1);        
                EnableWindow(handle, true);
            }
        }
    }
}
