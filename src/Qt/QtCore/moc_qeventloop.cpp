/****************************************************************************
** Meta object code from reading C++ file 'qeventloop.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qeventloop.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qeventloop.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10QEventLoopE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10QEventLoopE = QtMocHelpers::stringData(
    "QEventLoop",
    "exit",
    "",
    "returnCode",
    "quit",
    "ProcessEventsFlags",
    "ProcessEventsFlag",
    "AllEvents",
    "ExcludeUserInputEvents",
    "ExcludeSocketNotifiers",
    "WaitForMoreEvents",
    "X11ExcludeTimers",
    "EventLoopExec",
    "DialogExec",
    "ApplicationExec"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10QEventLoopE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       1,   37, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x0a,    2 /* Public */,
       1,    0,   35,    2, 0x2a,    4 /* Public | MethodCloned */,
       4,    0,   36,    2, 0x0a,    5 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
       5,    6, 0x1,    8,   42,

 // enum data: key, value
       7, uint(QEventLoop::AllEvents),
       8, uint(QEventLoop::ExcludeUserInputEvents),
       9, uint(QEventLoop::ExcludeSocketNotifiers),
      10, uint(QEventLoop::WaitForMoreEvents),
      11, uint(QEventLoop::X11ExcludeTimers),
      12, uint(QEventLoop::EventLoopExec),
      13, uint(QEventLoop::DialogExec),
      14, uint(QEventLoop::ApplicationExec),

       0        // eod
};

Q_CONSTINIT const QMetaObject QEventLoop::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN10QEventLoopE.offsetsAndSizes,
    qt_meta_data_ZN10QEventLoopE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10QEventLoopE_t,
        // enum 'ProcessEventsFlags'
        QtPrivate::TypeAndForceComplete<QEventLoop::ProcessEventsFlags, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QEventLoop, std::true_type>,
        // method 'exit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'exit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QEventLoop::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QEventLoop *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->exit((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->exit(); break;
        case 2: _t->quit(); break;
        default: ;
        }
    }
}

const QMetaObject *QEventLoop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QEventLoop::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10QEventLoopE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QEventLoop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
