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
#ifdef _WIN32_WCE //Q_OS_WINCE

#include <windows.h>
#include <winbase.h>
#include <kfuncs.h>
#include <stdio.h>
#include <altcecrt.h>

#include "qplatformdefs.h"
#include "qfunctions_wince.h"
#include "qstring.h"
#include "qbytearray.h"
#include "qhash.h"

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")

QT_USE_NAMESPACE

#ifdef __cplusplus
extern "C" {
#endif

wchar_t* CEPrivConvCharToWide(const char* string)
{
	size_t length = strlen(string);
	wchar_t* wString = new wchar_t[length +1];
	for (unsigned int i = 0; i < (length +1); i++)
		wString[i] = string[i];
	return wString;
}

// Time -------------------------------------------------------------
time_t ftToTime_t( const FILETIME ft )
{
    ULARGE_INTEGER li;
    li.LowPart  = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;

    // 100-nanosec to seconds
    li.QuadPart /= 10000000;

    // FILETIME is from 1601-01-01 T 00:00:00
    // time_t   is from 1970-01-01 T 00:00:00
    // 1970 - 1601 = 369 year (89 leap years)
    //
    // ((369y*365d) + 89d) *24h *60min *60sec
    // = 11644473600 seconds
    li.QuadPart -= 11644473600;
    return li.LowPart; 
}

FILETIME time_tToFt( time_t tt )
{
    ULARGE_INTEGER li;
    li.QuadPart  = tt;
    li.QuadPart += 11644473600;
    li.QuadPart *= 10000000;
    
    FILETIME ft;
    ft.dwLowDateTime = li.LowPart;
    ft.dwHighDateTime = li.HighPart;
    return ft; 
}

// File I/O ---------------------------------------------------------
int errno = 0;

int _getdrive( void ) 
{ 
    return 1; 
}

int _waccess( const WCHAR *path, int pmode )
{ 
    DWORD res = GetFileAttributes( path );
    if ( 0xFFFFFFFF == res )
	return -1;

    if ( (pmode & W_OK) && (res & FILE_ATTRIBUTE_READONLY) ) 
	return -1;
    
    if ( (pmode & X_OK) && !(res & FILE_ATTRIBUTE_DIRECTORY) ) {
	QString file = QString::fromUtf16(reinterpret_cast<const ushort *> (path));
	if ( !(file.endsWith(QString::fromLatin1(".exe")) || 
	       file.endsWith(QString::fromLatin1(".com"))) )
	    return -1;
    }

    return 0;
}

int open( const char *filename, int oflag, int pmode ) 
{ 
    QString fn( QString::fromLatin1(filename) );
    return _wopen( (WCHAR*)fn.utf16(), oflag, pmode );
}

int _wopen( const WCHAR *filename, int oflag, int /*pmode*/ ) 
{
    WCHAR *flag;

	if ( oflag & _O_APPEND ) {
		if ( oflag & _O_WRONLY ) {
			flag = L"a";
		} else if ( oflag & _O_RDWR ) {
			flag = L"a+";
		}
	} else if (oflag & _O_BINARY) {
		if ( oflag & _O_WRONLY ) {
			flag = L"wb";
		} else if ( oflag & _O_RDWR ) {
			flag = L"w+b"; // slightly different from "r+" where the file must exist
		} else if ( oflag & _O_RDONLY ) {
			flag = L"rb";
		} else {
			flag = L"b";
		}
	} else {
		if ( oflag & _O_WRONLY ) {
			flag = L"wt";
		} else if ( oflag & _O_RDWR ) {
			flag = L"w+t"; // slightly different from "r+" where the file must exist
		} else if ( oflag & _O_RDONLY ) {
			flag = L"rt";
		} else {
			flag = L"t";
		}
	}

    int retval = (int)_wfopen( filename, flag );
    return (retval == NULL) ? -1 : retval;
} 

long _lseek( int handle, long offset, int origin )
{
    return fseek( (FILE*)handle, offset, origin );
}

int _read( int handle, void *buffer, unsigned int count ) 
{ 
    return fread( buffer, 1, count, (FILE*)handle );
}

int _write( int handle, const void *buffer, unsigned int count )
{ 
    return fwrite( buffer, 1, count, (FILE*)handle );
}

int _close( int handle ) 
{ 
    if ( !handle )
	return 0;
    return fclose( (FILE*)handle );
}

FILE *_fdopen(int handle, const char* /*mode*/) 
{ 
    return (FILE*)handle; 
}

FILE *fdopen( int handle, const char* /*mode*/ ) 
{ 
    return (FILE*)handle;
}

void rewind( FILE *stream ) 
{ 
    fseek( stream, 0L, SEEK_SET ); 
}

int __fileno(FILE *f)
{
	return (int) _fileno(f);
}

FILE *tmpfile( void )
{ 
    static long i = 0; 
    char name[16]; 
    sprintf( name, "tmp%i", i++ ); 
    return fopen( name, "r+" ); 
}

int _mkdir(const char *dirname)
{
    return CreateDirectory(reinterpret_cast<const wchar_t *> (QString(QString::fromLatin1(dirname)).utf16()), 0) ? 0 : -1;
}

int _rmdir(const char *dirname)
{
    return RemoveDirectory(reinterpret_cast<const wchar_t *> (QString::fromLatin1(dirname).utf16())) ? 0 : -1;
}

int _access( const char *path, int pmode )
{
    return _waccess(reinterpret_cast<const wchar_t *> (QString::fromLatin1(path).utf16()),pmode);
}

int _rename( const char *oldname, const char *newname )
{
    return !MoveFile(reinterpret_cast<const wchar_t *> (QString::fromLatin1(oldname).utf16()), reinterpret_cast<const wchar_t *> (QString::fromLatin1(newname).utf16()));
}

int _remove( const char *name )
{
    return !DeleteFile(reinterpret_cast<const wchar_t *> (QString::fromLatin1(name).utf16()));
}

int stat( const char *path, struct stat *buffer )
{
    WIN32_FIND_DATA finfo;
    HANDLE ff = FindFirstFile( reinterpret_cast<const wchar_t *> (QString::fromLatin1(path).utf16()), &finfo );

    if ( ff == INVALID_HANDLE_VALUE )
	return -1;

    buffer->st_ctime = ftToTime_t( finfo.ftCreationTime );
    buffer->st_atime = ftToTime_t( finfo.ftLastAccessTime );
    buffer->st_mtime = ftToTime_t( finfo.ftLastWriteTime );
    buffer->st_nlink = 0;
    buffer->st_size  = finfo.nFileSizeLow; // ### missing high!
    buffer->st_mode  = (finfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? _S_IFDIR : _S_IFREG;
    buffer->st_mode |= (finfo.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? _O_RDONLY : _O_RDWR;
    return (FindClose(ff) == 0);
}

int _fstat( int handle, struct stat *buffer)
{
	BY_HANDLE_FILE_INFORMATION fInfo;
	BOOL res = GetFileInformationByHandle((HANDLE)handle, &fInfo);

    buffer->st_ctime = ftToTime_t( fInfo.ftCreationTime );
    buffer->st_atime = ftToTime_t( fInfo.ftLastAccessTime );
    buffer->st_mtime = ftToTime_t( fInfo.ftLastWriteTime );
    buffer->st_nlink = 0;
    buffer->st_size  = fInfo.nFileSizeLow; // ### missing high!
    buffer->st_mode  = (fInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? _S_IFDIR : _S_IFREG;
    buffer->st_mode |= (fInfo.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? _O_RDONLY : _O_RDWR;
	return (res == 0);
}

int SetErrorMode(int newValue)
{
	static int oldValue;
	int result = oldValue;
	oldValue = newValue;
	return result;
}

HRESULT CoInitialize(void* reserved)
{
	return CoInitializeEx(reserved, 0);
}

bool _chmod(const char *file, int mode)
{
    return _wchmod( reinterpret_cast<const wchar_t *> (QString::fromLatin1(file).utf16()), mode);
}

bool _wchmod(const WCHAR *file, int mode)
{
	// ### Does not work properly, what about just adding one property?
	if(mode&_S_IWRITE) {
		return SetFileAttributes(file, FILE_ATTRIBUTE_NORMAL);
	} else if((mode&_S_IREAD) && !(mode&_S_IWRITE)) {
		return SetFileAttributes(file, FILE_ATTRIBUTE_READONLY);
	}
	return false;
}

HANDLE CreateFileA(LPCSTR filename, DWORD access, DWORD share, LPSECURITY_ATTRIBUTES attr, DWORD dispo, DWORD flags, HANDLE tempFile)
{
    return CreateFileW( reinterpret_cast<const wchar_t *>(QString::fromLatin1(filename).utf16()), access, share, attr, dispo, flags, tempFile);
}

// Graphics ---------------------------------------------------------
BOOL SetWindowOrgEx( HDC /*hdc*/, int /*X*/, int /*Y*/, LPPOINT /*lpPoint*/) {
    return TRUE;
}

// Threading --------------------------------------------------------
HANDLE _beginthread(void( *start_address )( void * ), unsigned stack_size, void *arglist)
{
	return CreateThread(NULL, stack_size, (LPTHREAD_START_ROUTINE)start_address, arglist, 0, NULL);
}

unsigned long _beginthreadex( void *security, 
			      unsigned stack_size,
			      unsigned (__stdcall *start_address)(void *),
			      void *arglist, 
			      unsigned initflag, 
			      unsigned *thrdaddr) {
    return (unsigned long)
	CreateThread( (LPSECURITY_ATTRIBUTES)security,
		      (DWORD)stack_size, 
		      (LPTHREAD_START_ROUTINE)start_address,
		      (LPVOID)arglist, 
		      (DWORD)initflag | CREATE_SUSPENDED, 
		      (LPDWORD)thrdaddr);
}

void _endthreadex(unsigned nExitCode) {
    ExitThread((DWORD)nExitCode);
}

void *bsearch(const void *key,
	       const void *base,
	       size_t num,
	       size_t size,
	       int (__cdecl *compare)(const void *, const void *))
{
    size_t low = 0;
    size_t high = num - 1;
    while (low <= high) {
        unsigned int mid = ((unsigned) (low + high)) >> 1;
        int c = compare(key, (char*)base + mid * size);
        if (c < 0)
            high = mid - 1;
        else if (c > 0)
            low = mid + 1;
        else 
            return (char*) base + mid * size;
    }
    return (NULL);
} 

void *lfind(const void* key, const void* base, size_t* elements, size_t size,
            int (__cdecl *compare)(const void*, const void*))
{
    const char* current = (char*) base;
    const char* const end = (char*) (current + (*elements) * size);
    while (current != end) {
        if (compare(current, key) == 0)
            return (void*)current;
        current += size;
    }
    return 0;
}

DWORD GetThreadLocale(void) {
	return GetUserDefaultLCID();
}

void abort()
{
    exit(3);
}

void *calloc( size_t num, size_t size )
{
    void *ptr = malloc( num * size );
    if( ptr )
	memset( ptr, 0, num * size );
    return ptr;
}

// _getpid is currently only used for creating a temporary filename
// therefore we return a random number inside of the process ID range
int _getpid()
{
	return qrand() % 32;
}

#ifdef __cplusplus
} // extern "C"
#endif
// Environment ------------------------------------------------------
inline QHash<QByteArray, QByteArray>& qt_app_environment()
{
    static QHash<QByteArray, QByteArray> internalEnvironment;
    return internalEnvironment;
}

errno_t getenv_s(size_t* sizeNeeded, char* buffer, size_t bufferSize, const char* varName)
{
    if (!sizeNeeded)
        return EINVAL;

    if (!qt_app_environment().contains(varName)) {
        if (buffer)
            buffer[0] = '\0';
        return ENOENT;
    }
    
    QByteArray value = qt_app_environment().value(varName);
    if (!value.endsWith('\0')) // win32 guarantees terminated string
        value.append('\0');
    
    if (bufferSize < (size_t)value.size()) {
        *sizeNeeded = value.size();
        return 0;
    }
    
    strcpy(buffer, value.constData());
    return 0;
}

errno_t _putenv_s(const char* varName, const char* value)
{
    QByteArray input = value;
    if (input.isEmpty()) {
        if (qt_app_environment().contains(varName))
            qt_app_environment().remove(varName);
    } else {
        // win32 guarantees terminated string
        if (!input.endsWith('\0'))
            input.append('\0');
        qt_app_environment()[varName] = input;
    }

    return 0;
}

#endif // Q_OS_WINCE
