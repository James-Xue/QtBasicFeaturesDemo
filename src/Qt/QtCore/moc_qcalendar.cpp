/****************************************************************************
** Meta object code from reading C++ file 'qcalendar.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qcalendar.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcalendar.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9QCalendarE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN9QCalendarE = QtMocHelpers::stringData(
    "QCalendar",
    "System",
    "Gregorian",
    "Julian",
    "Milankovic",
    "Jalali",
    "IslamicCivil",
    "Last",
    "User"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN9QCalendarE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x2,    7,   19,

 // enum data: key, value
       2, uint(QCalendar::System::Gregorian),
       3, uint(QCalendar::System::Julian),
       4, uint(QCalendar::System::Milankovic),
       5, uint(QCalendar::System::Jalali),
       6, uint(QCalendar::System::IslamicCivil),
       7, uint(QCalendar::System::Last),
       8, uint(QCalendar::System::User),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCalendar::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_ZN9QCalendarE.offsetsAndSizes,
    qt_meta_data_ZN9QCalendarE,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN9QCalendarE_t,
        // enum 'System'
        QtPrivate::TypeAndForceComplete<QCalendar::System, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCalendar, std::true_type>
    >,
    nullptr
} };

QT_WARNING_POP
