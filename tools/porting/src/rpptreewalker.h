/****************************************************************************
**
** Copyright (C) 2004-2005 Trolltech AS. All rights reserved.
**
** This file is part of the qt3to4 porting application of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef RPPTREEWALKER_H
#define RPPTREEWALKER_H

#include "rpp.h"

namespace Rpp {

class RppTreeWalker
{
public:
    virtual ~RppTreeWalker(){};
    virtual void evaluateItem(const Item *item);
    virtual void evaluateItemComposite(const ItemComposite *itemComposite);
    virtual void evaluateSource(const Source *source);
    virtual void evaluateDirective(const Directive *directive);
    virtual void evaluateIfSection(const IfSection *ifSection);
    virtual void evaluateConditionalDirective(const ConditionalDirective *conditionalDirective);

    virtual void evaluateText(const Text *textLine) {Q_UNUSED(textLine);}
    virtual void evaluateEmptyDirective(const EmptyDirective *directive) {Q_UNUSED(directive);}
    virtual void evaluateErrorDirective(const ErrorDirective *directive) {Q_UNUSED(directive);}
    virtual void evaluatePragmaDirective(const PragmaDirective *directive) {Q_UNUSED(directive);}
    virtual void evaluateIncludeDirective(const IncludeDirective *directive) {Q_UNUSED(directive);}
    virtual void evaluateDefineDirective(const DefineDirective *directive) {Q_UNUSED(directive);}
    virtual void evaluateUndefDirective(const UndefDirective *directive) {Q_UNUSED(directive);}
    virtual void evaluateLineDirective(const LineDirective *directive) {Q_UNUSED(directive);}
    virtual void evaluateNonDirective(const NonDirective *directive) {Q_UNUSED(directive);}

    virtual void evaluateIfdefDirective(const IfdefDirective *directive);
    virtual void evaluateIfndefDirective(const IfndefDirective *directive);
    virtual void evaluateIfDirective(const IfDirective *directive);
    virtual void evaluateElifDirective(const ElifDirective *directive);
    virtual void evaluateElseDirective(const ElseDirective *directive);

    virtual void evaluateEndifDirective(const EndifDirective *directive) {Q_UNUSED(directive);}
};

}

#endif
