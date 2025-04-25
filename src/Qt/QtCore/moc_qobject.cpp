/****************************************************************************
** Meta object code from reading C++ file 'qobject.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qobject.h"
#include <QtCore/qmetatype.h>
#include <QtCore/qproperty.h>
#include <QtCore/qtmochelpers.h>
#include <memory>
#include <QtCore/qxptype_traits.h>

#if !defined(Q_MOC_OUTPUT_REVISION)
    #error "The header file 'qobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
    #error "This file was generated using the moc from 6.8.2. It"
    #error "cannot be used with the include files from this version of Qt."
    #error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN7QObjectE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN7QObjectE = QtMocHelpers::stringData(
    "QObject",
    "destroyed",
    "",
    "objectNameChanged",
    "objectName",
    "deleteLater",
    "parent"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN7QObjectE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   50, // properties
       0,    0, // enums/sets
       2,   55, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    2 /* Public */,
       1,    0,   41,    2, 0x26,    4 /* Public | MethodCloned */,
       3,    1,   42,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   45,    2, 0x0a,    7 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,

 // constructors: parameters
    0x80000000 | 2, QMetaType::QObjectStar,    6,
    0x80000000 | 2,

 // properties: name, type, flags, notifyId, revision
       4, QMetaType::QString, 0x02015103, uint(2), 0,

 // constructors: name, argc, parameters, tag, flags, initial metatype offsets
       0,    1,   46,    2, 0x0e,    8 /* Public */,
       0,    0,   49,    2, 0x2e,    9 /* Public | MethodCloned */,

       0        // eod
};

Q_CONSTINIT const QMetaObject QObject::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN7QObjectE.offsetsAndSizes,
    qt_meta_data_ZN7QObjectE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN7QObjectE_t,
        // property 'objectName'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QObject, std::true_type>,
        // method 'destroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QObject *, std::false_type>,
        // method 'destroyed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'objectNameChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'deleteLater'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // constructor 'QObject'
        QtPrivate::TypeAndForceComplete<QObject *, std::false_type>
    >,
    nullptr
} };

void QObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QObject *>(_o);
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { QObject *_r = new QObject((*reinterpret_cast<std::add_pointer_t<QObject*>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { QObject *_r = new QObject();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
    if (_c == QMetaObject::ConstructInPlace) {
        switch (_id) {
        case 0: { new (_a[0]) QObject((*reinterpret_cast<std::add_pointer_t<QObject*>>(_a[1]))); } break;
        case 1: { new (_a[0]) QObject(); } break;
        default: break;
        }
    }
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->destroyed((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1]))); break;
        case 1: _t->destroyed(); break;
        case 2: _t->objectNameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])), QPrivateSignal()); break;
        case 3: _t->deleteLater(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QObject::*)(QObject * );
            if (_q_method_type _q_method = &QObject::destroyed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QObject::*)(const QString & , QPrivateSignal);
            if (_q_method_type _q_method = &QObject::objectNameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->objectName(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setObjectName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    }
    if (_c == QMetaObject::BindableProperty) {
        switch (_id) {
        case 0: *static_cast<QUntypedBindable *>(_a[0]) = _t->bindableObjectName(); break;
        default: break;
        }
    }
}

const QMetaObject *QObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN7QObjectE.stringdata0))
        return static_cast<void*>(this);
    return nullptr;
}

int QObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QObject::destroyed(QObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void QObject::objectNameChanged(const QString & _t1, QPrivateSignal _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
