// Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Marc Mutz <marc.mutz@kdab.com>

#ifndef QWAITCONDITION_P_H
#define QWAITCONDITION_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists for the convenience of
// qmutex.cpp and qmutex_unix.cpp. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qwaitcondition.h>
#include <QtCore/qmutex.h>
#include <QtCore/qdeadlinetimer.h>
#include <QtCore/private/qglobal_p.h>
#include <condition_variable>
#include <mutex>

QT_BEGIN_NAMESPACE

namespace QtPrivate {
// Ideal alignment for mutex and condition_variable: it's the hardware
// interference size (size of a cache line) if the types are likely to contain
// the actual data structures, otherwise just that of a pointer.
inline constexpr quintptr IdealMutexAlignment =
        sizeof(std::mutex) > sizeof(void *) &&
        sizeof(std::condition_variable) > sizeof(void *) ?
            64 : alignof(void*);

} // namespace QtPrivate

QT_END_NAMESPACE

#endif /* QWAITCONDITION_P_H */
