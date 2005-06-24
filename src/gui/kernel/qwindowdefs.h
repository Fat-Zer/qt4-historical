/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the gui module of the Qt Toolkit.
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

#ifndef QWINDOWDEFS_H
#define QWINDOWDEFS_H

#include "QtCore/qobjectdefs.h"
#include "QtCore/qnamespace.h"

// Class forward definitions

class QPaintDevice;
class QWidget;
class QDialog;
class QColor;
class QPalette;
#ifdef QT3_SUPPORT
class QColorGroup;
#endif
class QCursor;
class QPoint;
class QSize;
class QRect;
class QPolygon;
class QPainter;
class QRegion;
class QFont;
class QFontMetrics;
class QFontInfo;
class QPen;
class QBrush;
class QMatrix;
class QPixmap;
class QBitmap;
class QMovie;
class QImage;
class QPicture;
class QPrinter;
class QTimer;
class QTime;
class QClipboard;
class QString;
class QByteArray;
class QApplication;

template<typename T> class QList;
typedef QList<QWidget *> QWidgetList;

// Window system dependent definitions

#if defined(Q_WS_MAC)
#if (MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_2)
typedef struct OpaqueEventLoopTimerRef* EventLoopTimerRef;
typedef struct OpaqueMenuHandle *MenuRef;
#else
typedef struct __EventLoopTimer *EventLoopTimerRef;
typedef struct OpaqueMenuRef *MenuRef;
#endif
typedef char **MenuBarHandle;
typedef struct OpaqueDragRef *DragRef;
typedef struct OpaqueControlRef* ControlRef;
typedef ControlRef HIViewRef;
typedef struct CGImage *CGImageRef;
typedef struct CGContext *CGContextRef;
typedef struct OpaqueIconRef *IconRef;
typedef struct OpaqueWindowGroupRef *WindowGroupRef;
typedef struct OpaqueGrafPtr *CGrafPtr;
typedef struct OpaquePMPrintSession *PMPrintSession;
typedef struct OpaquePMPrintSettings *PMPrintSettings;
typedef struct OpaquePMPageFormat *PMPageFormat;
typedef struct OpaqueEventHandlerRef *EventHandlerRef;
typedef struct OpaqueEventHandlerCallRef *EventHandlerCallRef;
typedef struct OpaqueEventRef *EventRef;
typedef long int OSStatus;
typedef struct OpaqueScrapRef *ScrapRef;
typedef struct OpaqueRgnHandle *RgnHandle;
typedef struct OpaqueWindowPtr *WindowPtr;
typedef WindowPtr WindowRef;
typedef struct OpaqueGrafPtr *GWorldPtr;
typedef GWorldPtr GrafPtr;
typedef struct GDevice **GDHandle;
typedef void * MSG;
typedef int WId;
typedef struct AEDesc AppleEvent;
#endif // Q_WS_MAC

#if defined(Q_WS_WIN)
#include "QtGui/qwindowdefs_win.h"
#endif // Q_WS_WIN


#if defined(Q_OS_TEMP)
#include "qwinfunctions_wce.h"
#endif // Q_OS_TEMP

#if defined(Q_WS_X11)

typedef struct _XDisplay Display;
typedef union  _XEvent XEvent;
typedef struct _XGC *GC;
typedef struct _XRegion *Region;
typedef unsigned long  WId;

#endif // Q_WS_X11

#if defined(Q_WS_QWS)

typedef unsigned long  WId;
struct QWSEvent;

#endif // Q_WS_QWS

template<class K, class V> class QHash;
typedef QHash<WId, QWidget *> QWidgetMapper;

#if defined(QT_NEEDS_QMAIN)
#define main qMain
#endif

// Global platform-independent types and functions

#endif // QWINDOWDEFS_H
