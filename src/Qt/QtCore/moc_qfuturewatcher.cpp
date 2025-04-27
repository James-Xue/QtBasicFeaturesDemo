/****************************************************************************
** Meta object code from reading C++ file 'qfuturewatcher.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qfuturewatcher.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qfuturewatcher.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18QFutureWatcherBaseE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN18QFutureWatcherBaseE = QtMocHelpers::stringData(
    "QFutureWatcherBase",
    "started",
    "",
    "finished",
    "canceled",
    "paused",
    "suspending",
    "suspended",
    "resumed",
    "resultReadyAt",
    "resultIndex",
    "resultsReadyAt",
    "beginIndex",
    "endIndex",
    "progressRangeChanged",
    "minimum",
    "maximum",
    "progressValueChanged",
    "progressValue",
    "progressTextChanged",
    "progressText",
    "cancel",
    "setSuspended",
    "suspend",
    "resume",
    "toggleSuspended",
    "setPaused",
    "pause",
    "togglePaused"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN18QFutureWatcherBaseE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  134,    2, 0x06,    1 /* Public */,
       3,    0,  135,    2, 0x06,    2 /* Public */,
       4,    0,  136,    2, 0x06,    3 /* Public */,
       5,    0,  137,    2, 0x06,    4 /* Public */,
       6,    0,  138,    2, 0x06,    5 /* Public */,
       7,    0,  139,    2, 0x06,    6 /* Public */,
       8,    0,  140,    2, 0x06,    7 /* Public */,
       9,    1,  141,    2, 0x06,    8 /* Public */,
      11,    2,  144,    2, 0x06,   10 /* Public */,
      14,    2,  149,    2, 0x06,   13 /* Public */,
      17,    1,  154,    2, 0x06,   16 /* Public */,
      19,    1,  157,    2, 0x06,   18 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      21,    0,  160,    2, 0x0a,   20 /* Public */,
      22,    1,  161,    2, 0x0a,   21 /* Public */,
      23,    0,  164,    2, 0x0a,   23 /* Public */,
      24,    0,  165,    2, 0x0a,   24 /* Public */,
      25,    0,  166,    2, 0x0a,   25 /* Public */,
      26,    1,  167,    2, 0x0a,   26 /* Public */,
      27,    0,  170,    2, 0x0a,   28 /* Public */,
      28,    0,  171,    2, 0x0a,   29 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   15,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::QString,   20,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QFutureWatcherBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN18QFutureWatcherBaseE.offsetsAndSizes,
    qt_meta_data_ZN18QFutureWatcherBaseE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN18QFutureWatcherBaseE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QFutureWatcherBase, std::true_type>,
        // method 'started'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'finished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'canceled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paused'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'suspending'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'suspended'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resumed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resultReadyAt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'resultsReadyAt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'progressRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'progressValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'progressTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'cancel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setSuspended'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'suspend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resume'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleSuspended'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setPaused'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'pause'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'togglePaused'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QFutureWatcherBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QFutureWatcherBase *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->started(); break;
        case 1: _t->finished(); break;
        case 2: _t->canceled(); break;
        case 3: _t->paused(); break;
        case 4: _t->suspending(); break;
        case 5: _t->suspended(); break;
        case 6: _t->resumed(); break;
        case 7: _t->resultReadyAt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->resultsReadyAt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 9: _t->progressRangeChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->progressValueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->progressTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->cancel(); break;
        case 13: _t->setSuspended((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->suspend(); break;
        case 15: _t->resume(); break;
        case 16: _t->toggleSuspended(); break;
        case 17: _t->setPaused((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: _t->pause(); break;
        case 19: _t->togglePaused(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (QFutureWatcherBase::*)();
            if (_q_method_type _q_method = &QFutureWatcherBase::started; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)();
            if (_q_method_type _q_method = &QFutureWatcherBase::finished; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)();
            if (_q_method_type _q_method = &QFutureWatcherBase::canceled; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)();
            if (_q_method_type _q_method = &QFutureWatcherBase::paused; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)();
            if (_q_method_type _q_method = &QFutureWatcherBase::suspending; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)();
            if (_q_method_type _q_method = &QFutureWatcherBase::suspended; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)();
            if (_q_method_type _q_method = &QFutureWatcherBase::resumed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)(int );
            if (_q_method_type _q_method = &QFutureWatcherBase::resultReadyAt; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)(int , int );
            if (_q_method_type _q_method = &QFutureWatcherBase::resultsReadyAt; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)(int , int );
            if (_q_method_type _q_method = &QFutureWatcherBase::progressRangeChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)(int );
            if (_q_method_type _q_method = &QFutureWatcherBase::progressValueChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _q_method_type = void (QFutureWatcherBase::*)(const QString & );
            if (_q_method_type _q_method = &QFutureWatcherBase::progressTextChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject *QFutureWatcherBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QFutureWatcherBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN18QFutureWatcherBaseE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QFutureWatcherBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void QFutureWatcherBase::started()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QFutureWatcherBase::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QFutureWatcherBase::canceled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QFutureWatcherBase::paused()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QFutureWatcherBase::suspending()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QFutureWatcherBase::suspended()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QFutureWatcherBase::resumed()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QFutureWatcherBase::resultReadyAt(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QFutureWatcherBase::resultsReadyAt(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QFutureWatcherBase::progressRangeChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QFutureWatcherBase::progressValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QFutureWatcherBase::progressTextChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
