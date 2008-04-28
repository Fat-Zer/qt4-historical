/****************************************************************************
**
** Copyright (C) 1992-2006 TROLLTECH ASA. All rights reserved.
**
** This file is part of the Phone Edition of the Qt Toolkit.
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

#ifndef QTKEYSYM_H
#define QTKEYSYM_H

/* Special keys used by Qtopia, mapped into the X11 private keypad range */
#define QTOPIAXK_Select		0x11000601
#define QTOPIAXK_Yes		0x11000602
#define QTOPIAXK_No		0x11000603

#define QTOPIAXK_Cancel		0x11000604
#define QTOPIAXK_Printer	0x11000605
#define QTOPIAXK_Execute	0x11000606
#define QTOPIAXK_Sleep		0x11000607
#define QTOPIAXK_Play		0x11000608
#define QTOPIAXK_Zoom		0x11000609

#define QTOPIAXK_Context1	0x1100060A
#define QTOPIAXK_Context2	0x1100060B
#define QTOPIAXK_Context3	0x1100060C
#define QTOPIAXK_Context4	0x1100060D
#define QTOPIAXK_Call		0x1100060E
#define QTOPIAXK_Hangup		0x1100060F
#define QTOPIAXK_Flip		0x11000610

#define	QTOPIAXK_Min		QTOPIAXK_Select
#define	QTOPIAXK_Max		QTOPIAXK_Flip

#endif
