/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the item views module of the Qt Toolkit.
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

#ifndef QHEADERVIEW_P_H
#define QHEADERVIEW_P_H

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

#include <private/qabstractitemview_p.h>
#include <qbitarray.h>
#include <qapplication.h>
#include <qlabel.h>

class QHeaderViewPrivate: public QAbstractItemViewPrivate
{
    Q_DECLARE_PUBLIC(QHeaderView)

public:
    QHeaderViewPrivate()
        : state(NoState),
          offset(0),
          sortIndicatorOrder(Qt::AscendingOrder),
          sortIndicatorSection(0),
          sortIndicatorShown(false),
          lastPos(-1),
          section(-1),
          target(-1),
          pressed(-1),
          hover(-1),
          movableSections(false),
          clickableSections(false),
          highlightSelected(false),
          stretchLastSection(false),
          stretchSections(0),
          sectionIndicatorOffset(0),
          sectionIndicator(0),
          globalResizeMode(QHeaderView::Interactive) {}

    int sectionHandleAt(int position);
    void setupSectionIndicator(int section, int position);
    void updateSectionIndicator(int section, int position);

    bool isSectionSelected(int section) const;
    inline void prepareSectionSelected()
        { if (sectionSelection.count() != sections.count() * 2)
            sectionSelection.fill(false, sections.count() * 2);
          else sectionSelection.fill(false); }

    inline int defaultSectionSize() const
        { return (orientation == Qt::Horizontal ? 100 : 30); }

    inline bool reverse() const
        { return q_func()->isRightToLeft() && orientation == Qt::Horizontal; }

    enum State { NoState, ResizeSection, MoveSection } state;

    int offset;
    Qt::Orientation orientation;
    Qt::SortOrder sortIndicatorOrder;
    int sortIndicatorSection;
    bool sortIndicatorShown;

    struct HeaderSection {
        int position;
        int logical;
        uint hidden : 1;
        QHeaderView::ResizeMode mode;
        inline bool operator>(int position) const
            { return (*this).position > position; }
    };
    mutable QVector<HeaderSection> sections; // HeaderSection = sections.at(visualIndex)
    mutable QVector<int> visualIndices; // visualIndex = visualIndices.at(logicalIndex)
    mutable QBitArray sectionSelection;

    int lastPos;
    int section; // used for resizing and moving sections
    int target;
    int pressed;
    int hover;
    bool movableSections;
    bool clickableSections;
    bool highlightSelected;
    bool stretchLastSection;
    int stretchSections;
    int sectionIndicatorOffset;
    QLabel *sectionIndicator;
    QStyleOptionHeader getStyleOption() const;
    QHeaderView::ResizeMode globalResizeMode;
};

#endif // QHEADERVIEW_P_H
