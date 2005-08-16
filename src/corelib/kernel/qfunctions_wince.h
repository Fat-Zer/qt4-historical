/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QFUNCTIONS_WCE_H
#define QFUNCTIONS_WCE_H
#ifdef Q_OS_WINCE
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <winbase.h>
#include <objbase.h>
#include <kfuncs.h>
#include <ctype.h>
#include <time.h>
#include <crtdefs.h>
#include <altcecrt.h>
#include <winsock.h>
#include <ceconfig.h>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

#ifdef QT_BUILD_CORE_LIB
QT_MODULE(Core)
#endif

QT_END_NAMESPACE
QT_END_HEADER


// The standard SDK misses this define...
#define _control87 _controlfp

#if !defined __cplusplus
#define bool int
#define true 1
#define false 0
#endif

// Environment ------------------------------------------------------
errno_t getenv_s(size_t*, char*, size_t, const char*);
errno_t _putenv_s(const char*, const char*);

#ifdef __cplusplus
extern "C" {
#endif

#define SetWindowLongA		SetWindowLong
#define GetWindowLongA		GetWindowLong
#define SendMessageA		SendMessage
#define calloc			_calloc

#if !defined(NO_ERRNO_H)
#define NO_ERRNO_H
#endif

// Environment ------------------------------------------------------
int _getpid(void);


// Time -------------------------------------------------------------
#ifndef _TM_DEFINED
#define _TM_DEFINED
struct tm {
    int tm_sec;     /* seconds after the minute - [0,59] */
    int tm_min;     /* minutes after the hour - [0,59] */
    int tm_hour;    /* hours since midnight - [0,23] */
    int tm_mday;    /* day of the month - [1,31] */
    int tm_mon;     /* months since January - [0,11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday - [0,6] */
    int tm_yday;    /* days since January 1 - [0,365] */
    int tm_isdst;   /* daylight savings time flag */
};
#endif // _TM_DEFINED

FILETIME time_tToFt( time_t tt );

// File I/O ---------------------------------------------------------
//#define PATH_MAX		  1024
#define _O_RDONLY		0x0001
#define _O_RDWR			0x0002
#define _O_WRONLY		0x0004
#define _O_CREAT		0x0008
#define _O_TRUNC		0x0010
#define _O_APPEND		0x0020
#define _O_EXCL			0x0040

#define O_RDONLY _O_RDONLY
#define O_RDWR _O_RDWR
#define O_WRONLY _O_WRONLY
#define O_CREAT _O_CREAT
#define O_TRUNC _O_TRUNC
#define O_APPEND _O_APPEND
#define O_EXCL _O_EXCL

#define _S_IFMT			0x0600
#define _S_IFDIR		0x0200
#define _S_IFCHR		0x0100
#define _S_IFREG		0x0400
#define _S_IREAD        0x0010
#define _S_IWRITE       0x0008

#define S_IFMT _S_IFMT
#define S_IFDIR _S_IFDIR
#define S_IFCHR _S_IFCHR
#define S_IFREG _S_IFREG
#define S_IREAD _S_IREAD
#define S_IWRITE _S_IWRITE

#define _IOFBF          0x0000
#define _IOLBF          0x0040
#define _IONBF          0x0004

// Regular Berkeley error constants
#ifndef _STAT_DEFINED
#define _STAT_DEFINED
struct stat
{
    int st_mode;
    int st_size;
    int st_nlink;
    time_t st_mtime;
    time_t st_atime;
    time_t st_ctime;
};
#endif

typedef int mode_t;
extern int errno;

int	_getdrive( void );
int	_waccess( const WCHAR *path, int pmode );
int	_wopen( const WCHAR *filename, int oflag, int pmode );
long	_lseek( int handle, long offset, int origin );
int	_read( int handle, void *buffer, unsigned int count );
int	_write( int handle, const void *buffer, unsigned int count );
int	_close( int handle );
FILE   *_fdopen(int handle, const char *mode);
FILE   *fdopen(int handle, const char *mode);
void	rewind( FILE *stream );
int __fileno(FILE *);
FILE   *tmpfile( void );

int _mkdir(const char *dirname);
int _rmdir(const char *dirname);
int _access( const char *path, int pmode );
int _rename( const char *oldname, const char *newname );
int _remove( const char *name );
int	open( const char *filename, int oflag, int pmode );
int stat( const char *path, struct stat *buffer );
int _fstat( int handle, struct stat *buffer);

#define SEM_FAILCRITICALERRORS 0x0001
#define SEM_NOOPENFILEERRORBOX 0x0002
int SetErrorMode(int);
HRESULT CoInitialize(void* reserved);

bool _chmod(const char *file, int mode);
bool _wchmod(const WCHAR *file, int mode);

#pragma warning(disable: 4273)
HANDLE CreateFileA(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

// Printer ----------------------------------------------------------
#define ETO_GLYPH_INDEX		0x0010

// Graphics ---------------------------------------------------------
#ifndef SM_CXCURSOR
#  define SM_CXCURSOR       13
#endif
#ifndef SM_CYCURSOR
#  define SM_CYCURSOR      14
#endif
BOOL SetWindowOrgEx( HDC hdc, int X, int Y, LPPOINT lpPoint );

// Other stuff ------------------------------------------------------
#define MWMO_ALERTABLE 0x0002
// ### not the real values
#define CREATE_NO_WINDOW	2
#define CF_HDROP		15

void abort();
void *calloc(size_t num, size_t size);

#if !defined(TLS_OUT_OF_INDEXES)
#  define TLS_OUT_OF_INDEXES 0xffffffff
#endif
DWORD GetThreadLocale(void);

HANDLE _beginthread(void( *start_address )( void * ), unsigned stack_size, void *arglist);
unsigned long _beginthreadex( void *security,
			      unsigned stack_size,
			      unsigned (__stdcall *start_address)(void *),
			      void *arglist,
			      unsigned initflag,
			      unsigned *thrdaddr );
void _endthreadex(unsigned nExitCode);


// bsearch is needed for building the tiff plugin
// otherwise it could go into qguifunctions_wce
void *bsearch(const void *key,
	       const void *base,
	       size_t num,
	       size_t size,
	       int (__cdecl *compare)(const void *, const void *));

// Missing typedefs
#ifndef _TIME_T_DEFINED
typedef unsigned long time_t;
#define _TIME_T_DEFINED
#endif
typedef HANDLE  HDROP;

#ifndef WS_THICKFRAME
#define WS_THICKFRAME	WS_DLGFRAME
#endif

typedef UINT    UWORD;

// Missing definitions: not necessary equal to their Win32 values
// (the goal is to just have a clean compilation of MFC)
#define WS_MAXIMIZE               0
#define WS_MINIMIZE               0
#ifndef WS_EX_TOOLWINDOW
#define WS_EX_TOOLWINDOW          0
#endif
#define WS_EX_NOPARENTNOTIFY      0
#define WM_ENTERIDLE              0x0121
#define WM_PRINT                  WM_PAINT
#define WM_NCCREATE               (0x0081)
#define WM_PARENTNOTIFY           0
#define WM_NCDESTROY              (WM_APP-1)
#ifndef SW_RESTORE
#define SW_RESTORE                (SW_SHOWNORMAL)
#endif
#define SW_NORMAL                 (SW_SHOWNORMAL)
#define WAIT_OBJECT_0             0x00000000L
#define DEFAULT_GUI_FONT          SYSTEM_FONT
#ifndef SWP_NOREDRAW
#define SWP_NOREDRAW               0
#endif
#define WSAGETSELECTEVENT(lParam) LOWORD(lParam)
#define HWND_TOPMOST              ((HWND)-1)
#define HWND_NOTOPMOST 	          ((HWND)-2)
#define PS_DOT                    2
#define PD_ALLPAGES               0
#define PD_USEDEVMODECOPIES       0
#define PD_NOSELECTION            0
#define PD_HIDEPRINTTOFILE        0
#define PD_NOPAGENUMS             0
#define CF_METAFILEPICT           3
#define MM_ANISOTROPIC            8
#define KF_ALTDOWN                0x2000
#define SPI_GETWORKAREA           48

#ifndef WM_SETCURSOR
	#define WM_SETCURSOR 0x0020
	#define IDC_ARROW           MAKEINTRESOURCE(32512)
	#define IDC_IBEAM           MAKEINTRESOURCE(32513)
	#define IDC_WAIT            MAKEINTRESOURCE(32514)
	#define IDC_CROSS           MAKEINTRESOURCE(32515)
	#define IDC_UPARROW         MAKEINTRESOURCE(32516)
	#define IDC_SIZE            MAKEINTRESOURCE(32646)
	#define IDC_ICON            MAKEINTRESOURCE(32512)
	#define IDC_SIZENWSE        MAKEINTRESOURCE(32642)
	#define IDC_SIZENESW        MAKEINTRESOURCE(32643)
	#define IDC_SIZEWE          MAKEINTRESOURCE(32644)
	#define IDC_SIZENS          MAKEINTRESOURCE(32645)
	#define IDC_SIZEALL         MAKEINTRESOURCE(32646)
	#define IDC_NO              MAKEINTRESOURCE(32648)
	#define IDC_APPSTARTING     MAKEINTRESOURCE(32650)
	#define IDC_HELP            MAKEINTRESOURCE(32651)
	#define IDC_HAND	    MAKEINTRESOURCE(32649)
#endif

#define GMEM_MOVEABLE             LMEM_MOVEABLE
//#define GMEM_FIXED                LMEM_FIXED
//#define GMEM_ZEROINIT             LMEM_ZEROINIT
//#define GMEM_INVALID_HANDLE       LMEM_INVALID_HANDLE
//#define GMEM_LOCKCOUNT            LMEM_LOCKCOUNT
#define GPTR                      LPTR

// WinCE: CESYSGEN prunes the following FRP defines,
// and INTERNET_TRANSFER_TYPE_ASCII breaks in wininet.h
#undef FTP_TRANSFER_TYPE_ASCII
#define FTP_TRANSFER_TYPE_ASCII 0x00000001
#undef FTP_TRANSFER_TYPE_BINARY
#define FTP_TRANSFER_TYPE_BINARY 0x00000002

typedef DWORD OLE_COLOR;

// Define the Windows Styles which are not defined by MS
#ifndef WS_POPUPWINDOW
#define WS_POPUPWINDOW WS_POPUP|WS_BORDER|WS_SYSMENU|WS_CAPTION
#endif

#ifndef WS_OVERLAPPEDWINDOW
#define WS_OVERLAPPEDWINDOW WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX
#endif

#ifndef WS_TILED
#define WS_TILED WS_OVERLAPPED
#endif

#ifndef WS_TILEDWINDOW
#define WS_TILEDWINDOW WS_OVERLAPPEDWINDOW
#endif

#ifndef WS_EX_CAPTIONOKBTN
#define WS_EX_CAPTIONOKBTN 0x80000000L
#endif

#ifndef WS_EX_NODRAG
#define WS_EX_NODRAG       0x40000000L
#endif

#ifdef __cplusplus
}	// Extern C.
#endif

#endif // Q_OS_WINCE
#endif // QFUNCTIONS_WCE_H
