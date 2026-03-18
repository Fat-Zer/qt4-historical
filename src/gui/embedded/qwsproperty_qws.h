/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** Licensees holding valid Qt Preview licenses may use this file in
** accordance with the Qt Preview License Agreement provided with the
** Software.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
** information about Qt Commercial License Agreements.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QWSPROPERTY_QWS_H
#define QWSPROPERTY_QWS_H

#include "QtGui/qwscommand_qws.h"

QT_MODULE(Gui)

/*********************************************************************
 *
 * Class: QWSPropertyManager
 *
 *********************************************************************/

#ifndef QT_NO_QWS_PROPERTIES

class QWSPropertyManager
{
public:
    enum Mode {
        PropReplace = 0,
        PropPrepend,
        PropAppend
    };

    // pre-defined properties
    enum Atom {
        PropSelection = 0
    };

    QWSPropertyManager();
    ~QWSPropertyManager();

    bool setProperty(int winId, int property, int mode, const char *data, int len);
    bool hasProperty(int winId, int property);
    bool removeProperty(int winId, int property);
    bool addProperty(int winId, int property);
    bool getProperty(int winId, int property, char *&data, int &len);
    bool removeProperties(int winId);

private:
    class Data;
    Data* d;
};

#endif // QT_NO_QWS_PROPERTIES

#endif // QWSPROPERTY_QWS_H
