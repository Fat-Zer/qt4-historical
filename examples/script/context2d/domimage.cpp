/****************************************************************************
**
** Copyright (C) 1992-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
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

#include "domimage.h"

#include <QVariant>

#include <qscriptcontext.h>

QScriptValue DomImage::s_self;

DomImage::DomImage()
{
}


int DomImage::width() const
{
    return m_image.width();
}


int DomImage::height() const
{
    return m_image.height();
}


QString DomImage::src() const
{
    return m_src;
}

void DomImage::setSrc(const QString &src)
{
    m_src = src;
    m_image = QImage(m_src);
}


QString DomImage::name() const
{
    return m_src;
}

static QScriptValue Image(QScriptContext *context, QScriptEngine *env)
{
    QScriptValue val = context->thisObject();
    DomImage *image = new DomImage();
    QScriptValue klass = env->newVariant(qVariantFromValue(image));
    klass.setPrototype(DomImage::s_self);
    return klass;
}


static QScriptValue width(QScriptContext *context, QScriptEngine *env)
{
    QScriptValue val = context->thisObject();

    DomImage *image = qvariant_cast<DomImage*> (val.toVariant());
    if (image)
        return QScriptValue(env, image->width());

    return QScriptValue(env, 0);
}


static QScriptValue height(QScriptContext *context, QScriptEngine *env)
{
    QScriptValue val = context->thisObject();

    DomImage *image = qvariant_cast<DomImage*> (val.toVariant());
    if (image)
        return QScriptValue(env, image->height());

    return QScriptValue(env, 0);
}


static QScriptValue setSrc(QScriptContext *context, QScriptEngine *env)
{
    QScriptValue val = context->thisObject();
    QString src  = context->argument(0).toString();

    DomImage *image = qvariant_cast<DomImage*> (val.toVariant());
    if (image)
        image->setSrc(src);

    return env->undefinedValue();
}


static QScriptValue name(QScriptContext *context, QScriptEngine *env)
{
    QScriptValue val = context->thisObject();

    DomImage *image = qvariant_cast<DomImage*> (val.toVariant());
    if (image)
        return QScriptValue(env, image->name());

    return QScriptValue(env, QString());
}


void DomImage::setup(QScriptEngine *e)
{
    qRegisterMetaType<DomImage>();

    e->globalObject().setProperty("Image",
                                  e->newFunction(::Image, 0));

    s_self = e->newObject();
    s_self.setProperty("setSrc", e->newFunction(&::setSrc, 1));
    s_self.setProperty("width", e->newFunction(&::width));
    s_self.setProperty("height", e->newFunction(&::height));
    s_self.setProperty("name", e->newFunction(&::name));

    e->setDefaultPrototype(qMetaTypeId<DomImage>(), s_self);
}
