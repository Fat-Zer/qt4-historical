/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the widgets module of the Qt Toolkit.
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

#ifndef QTEXTEDIT_P_H
#define QTEXTEDIT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <private/qabstractscrollarea_p.h>
#include <qtextdocumentfragment.h>
#include <qscrollbar.h>
#include <qtextcursor.h>
#include <qtextformat.h>
#include <qbasictimer.h>

class QMimeData;

class QTextEditPrivate : public QAbstractScrollAreaPrivate
{
    Q_DECLARE_PUBLIC(QTextEdit)
public:
    inline QTextEditPrivate()
        : doc(0), cursorOn(false),
	  readOnly(false),
          autoFormatting(QTextEdit::AutoNone), tabChangesFocus(false),
          mousePressed(false), mightStartDrag(false), lineWrap(QTextEdit::WidgetWidth), lineWrapColumnOrWidth(0),
          lastSelectionState(false), ignoreAutomaticScrollbarAdjustement(false), textFormat(Qt::AutoText),
          preferRichText(false)
    {}

    bool cursorMoveKeyEvent(QKeyEvent *e);

    void updateCurrentCharFormat();

    void indent();
    void outdent();

    void gotoNextTableCell();
    void gotoPreviousTableCell();

    void createAutoBulletList();

    void init(const QTextDocumentFragment &fragment = QTextDocumentFragment(),
              QTextDocument *document = 0);

    void startDrag();

    void paste(const QMimeData *source);
    void paint(QPainter *p, QPaintEvent *e);

    void setCursorPosition(const QPoint &pos);
    void setCursorPosition(int pos, QTextCursor::MoveMode mode = QTextCursor::MoveAnchor);

    void repaintContents(const QRectF &contentsRect);
    void repaintCursor();

    inline QPoint mapToContents(const QPoint &point) const
    { return QPoint(point.x() + hbar->value(), point.y() + vbar->value()); }

    void selectionChanged();

    inline int contentsX() const { return hbar->value(); }
    inline int contentsY() const { return vbar->value(); }
    inline int contentsWidth() const { return hbar->maximum() + viewport->width(); }
    inline int contentsHeight() const { return vbar->maximum() + viewport->height(); }

    bool pageUp(QTextCursor::MoveMode moveMode);
    bool pageDown(QTextCursor::MoveMode moveMode);

    void updateCurrentCharFormatAndSelection();

    void adjustScrollbars();

    void setClipboardSelection();

    void ensureVisible(int documentPosition);

    void emitCursorPosChanged(const QTextCursor &someCursor);

    void setBlinkingCursorEnabled(bool enable);

    void extendWordwiseSelection(int suggestedNewPosition, qreal mouseXPosition);
    void extendLinewiseSelection(int suggestedNewPosition);

    QTextDocument *doc;
    bool cursorOn;
    QTextCursor cursor;
    QTextCharFormat lastCharFormat;

    QTextCursor dndFeedbackCursor;

    bool readOnly; /* ### move to document? */

    QTextEdit::AutoFormatting autoFormatting;
    bool tabChangesFocus;

    QBasicTimer cursorBlinkTimer;
    QBasicTimer autoScrollTimer;
    QBasicTimer trippleClickTimer;
    QPoint trippleClickPoint;

    bool mousePressed;

    bool mightStartDrag;
    QPoint dragStartPos;
    QBasicTimer dragStartTimer;

    QTextEdit::LineWrapMode lineWrap;
    int lineWrapColumnOrWidth;

    bool lastSelectionState;

    bool ignoreAutomaticScrollbarAdjustement;

    // Qt3 COMPAT only
    // ### non-compat'ed append needs it, too
    Qt::TextFormat textFormat;
    bool preferRichText;

    QString anchorToScrollToWhenVisible;

    QTextCursor selectedWordOnDoubleClick;
    QTextCursor selectedLineOnDoubleClick;

    // for QTextBrowser:
    QTextCursor focusIndicator;
};

#endif // QTEXTEDIT_P_H
