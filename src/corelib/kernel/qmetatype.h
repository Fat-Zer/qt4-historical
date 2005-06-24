/****************************************************************************
**
** Copyright (C) 1992-2005 Trolltech AS. All rights reserved.
**
** This file is part of the core module of the Qt Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QMETATYPE_H
#define QMETATYPE_H

#include "QtCore/qdatastream.h"

#ifdef Bool
#error qmetatype.h must be included before any header file that define Bool
#endif

class Q_CORE_EXPORT QMetaType {
public:
    enum Type {
        // these are merged with QVariant
        Void = 0, Bool = 1, Int = 2, UInt = 3, Double = 6, QChar = 7,
        QString = 10, QByteArray = 12,

        VoidStar = 128, Long, Short, Char, ULong,
        UShort, UChar, Float, QObjectStar, QWidgetStar,
        User = 256
    };

    typedef void (*Destructor)(void *);
    typedef void *(*Constructor)(const void *);
    typedef void (*SaveOperator)(QDataStream &, const void *);
    typedef void (*LoadOperator)(QDataStream &, void *);

    static int registerType(const char *typeName, Destructor destructor,
                            Constructor constructor);
    static void registerStreamOperators(const char *typeName, SaveOperator saveOp,
                                        LoadOperator loadOp);
    static int type(const char *typeName);
    static const char *typeName(int type);
    static bool isRegistered(int type);
    static void *construct(int type, const void *copy);
    static void destroy(int type, void *data);
    static bool save(QDataStream &stream, int type, const void *data);
    static bool load(QDataStream &stream, int type, void *data);
};

template <typename T>
void qMetaTypeDeleteHelper(T *t)
{
    delete t;
}

template <typename T>
void *qMetaTypeConstructHelper(const T *t)
{
    if (!t)
        return new T;
    return new T(*static_cast<const T*>(t));
}

template <typename T>
void qMetaTypeSaveHelper(QDataStream &stream, const T *t)
{
    stream << *t;
}

template <typename T>
void qMetaTypeLoadHelper(QDataStream &stream, T *t)
{
    stream >> *t;
}

template <typename T>
int qRegisterMetaType(const char *typeName, T * = 0)
{
    typedef void*(*ConstructPtr)(const T*);
    ConstructPtr cptr = qMetaTypeConstructHelper<T>;
    typedef void(*DeletePtr)(T*);
    DeletePtr dptr = qMetaTypeDeleteHelper<T>;

    return QMetaType::registerType(typeName, reinterpret_cast<QMetaType::Destructor>(dptr),
                                   reinterpret_cast<QMetaType::Constructor>(cptr));
}

template <typename T>
void qRegisterMetaTypeStreamOperators(const char *typeName, T * = 0)
{
    typedef void(*SavePtr)(QDataStream &, const T *);
    typedef void(*LoadPtr)(QDataStream &, T *);
    SavePtr sptr = qMetaTypeSaveHelper<T>;
    LoadPtr lptr = qMetaTypeLoadHelper<T>;

    QMetaType::registerStreamOperators(typeName, reinterpret_cast<QMetaType::SaveOperator>(sptr),
                                       reinterpret_cast<QMetaType::LoadOperator>(lptr));
}

template <typename T>
struct QMetaTypeId
{
};

#define Q_DECLARE_METATYPE(TYPE) \
template <> \
struct QMetaTypeId<TYPE> \
{ \
    static int qt_metatype_id() \
    { \
       static int id = qRegisterMetaType<TYPE>(#TYPE); \
       return id; \
    } \
};

template<> struct QMetaTypeId<QString>
{ static inline int qt_metatype_id() { return QMetaType::QString; } };
template<> struct QMetaTypeId<int>
{ static inline int qt_metatype_id() { return QMetaType::Int; } };
template<> struct QMetaTypeId<uint>
{ static inline int qt_metatype_id() { return QMetaType::UInt; } };
template<> struct QMetaTypeId<bool>
{ static inline int qt_metatype_id() { return QMetaType::Bool; } };
template<> struct QMetaTypeId<double>
{ static inline int qt_metatype_id() { return QMetaType::Double; } };
template<> struct QMetaTypeId<QByteArray>
{ static inline int qt_metatype_id() { return QMetaType::QByteArray; } };
template<> struct QMetaTypeId<QChar>
{ static inline int qt_metatype_id() { return QMetaType::QChar; } };
template<> struct QMetaTypeId<void>
{ static inline int qt_metatype_id() { return QMetaType::VoidStar; } };
template<> struct QMetaTypeId<long>
{ static inline int qt_metatype_id() { return QMetaType::Long; } };
template<> struct QMetaTypeId<short>
{ static inline int qt_metatype_id() { return QMetaType::Short; } };
template<> struct QMetaTypeId<char>
{ static inline int qt_metatype_id() { return QMetaType::Char; } };
template<> struct QMetaTypeId<ulong>
{ static inline int qt_metatype_id() { return QMetaType::ULong; } };
template<> struct QMetaTypeId<ushort>
{ static inline int qt_metatype_id() { return QMetaType::UShort; } };
template<> struct QMetaTypeId<uchar>
{ static inline int qt_metatype_id() { return QMetaType::UChar; } };
template<> struct QMetaTypeId<float>
{ static inline int qt_metatype_id() { return QMetaType::Float; } };
class QObject;
template<> struct QMetaTypeId<QObject *>
{ static inline int qt_metatype_id() { return QMetaType::QObjectStar; } };
class QWidget;
template<> struct QMetaTypeId<QWidget *>
{ static inline int qt_metatype_id() { return QMetaType::QWidgetStar; } };

#endif // QMETATYPE_H
