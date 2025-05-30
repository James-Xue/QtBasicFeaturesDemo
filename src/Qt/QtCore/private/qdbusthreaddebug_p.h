// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QDBUSTHREADDEBUG_P_H
#define QDBUSTHREADDEBUG_P_H

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

#include <QtDBus/private/qtdbusglobal_p.h>

#ifndef QT_NO_DBUS

#if !defined(QDBUS_THREAD_DEBUG) && defined(QT_BUILD_INTERNAL)
# define QDBUS_THREAD_DEBUG 1
#endif

#if QDBUS_THREAD_DEBUG
QT_BEGIN_NAMESPACE
typedef void (*qdbusThreadDebugFunc)(int, int, QDBusConnectionPrivate *);
Q_DBUS_EXPORT void qdbusDefaultThreadDebug(int, int, QDBusConnectionPrivate *);
extern Q_DBUS_EXPORT qdbusThreadDebugFunc qdbusThreadDebug;
QT_END_NAMESPACE
#endif

enum ThreadAction {
    ConnectAction = 0,
    DisconnectAction = 1,
    RegisterObjectAction = 2,
    UnregisterObjectAction = 3,
    ObjectRegisteredAtAction = 4,

    CloseConnectionAction = 10,
    ObjectDestroyedAction = 11,
    RelaySignalAction = 12,
    HandleObjectCallAction = 13,
    HandleSignalAction = 14,
    ConnectRelayAction = 15,
    DisconnectRelayAction = 16,
    FindMetaObject1Action = 17,
    FindMetaObject2Action = 18,
    RegisterServiceAction = 19,
    UnregisterServiceAction = 20,
    UpdateSignalHookOwnerAction = 21,
    HandleObjectCallPostEventAction = 22,
    HandleObjectCallSemaphoreAction = 23,
    DoDispatchAction = 24,
    SetDispatchEnabledAction = 25,
    MessageResultReceivedAction = 26,
    ActivateSignalAction = 27,
    PendingCallBlockAction = 28,
    SendMessageAction = 29,
    HuntAndEmitAction = 30,
};

struct QDBusLockerBase
{
    enum Condition
    {
        BeforeLock,
        AfterLock,
        BeforeUnlock,
        AfterUnlock,

        BeforePost,
        AfterPost,
        BeforeDeliver,
        AfterDeliver,

        BeforeAcquire,
        AfterAcquire,
        BeforeRelease,
        AfterRelease
    };

#if QDBUS_THREAD_DEBUG
    static inline void reportThreadAction(int action, int condition, QDBusConnectionPrivate *ptr)
    { if (qdbusThreadDebug) qdbusThreadDebug(action, condition, ptr); }
#else
    static inline void reportThreadAction(int, int, QDBusConnectionPrivate *) { }
#endif
};

struct QDBusReadLocker: QDBusLockerBase
{
    QDBusConnectionPrivate *self;
    ThreadAction action;
    Q_NODISCARD_CTOR QDBusReadLocker(ThreadAction a, QDBusConnectionPrivate *s)
        : self(s), action(a)
    {
        reportThreadAction(action, BeforeLock, self);
        self->lock.lockForRead();
        reportThreadAction(action, AfterLock, self);
    }

    inline ~QDBusReadLocker()
    {
        reportThreadAction(action, BeforeUnlock, self);
        self->lock.unlock();
        reportThreadAction(action, AfterUnlock, self);
    }
};

struct QDBusWriteLocker: QDBusLockerBase
{
    QDBusConnectionPrivate *self;
    ThreadAction action;
    Q_NODISCARD_CTOR QDBusWriteLocker(ThreadAction a, QDBusConnectionPrivate *s)
        : self(s), action(a)
    {
        reportThreadAction(action, BeforeLock, self);
        self->lock.lockForWrite();
        reportThreadAction(action, AfterLock, self);
    }

    inline ~QDBusWriteLocker()
    {
        reportThreadAction(action, BeforeUnlock, self);
        self->lock.unlock();
        reportThreadAction(action, AfterUnlock, self);
    }
};

#if QDBUS_THREAD_DEBUG
# define SEM_ACQUIRE(action, sem)                                       \
    do {                                                                \
    QDBusLockerBase::reportThreadAction(action, QDBusLockerBase::BeforeAcquire, this); \
    sem.acquire();                                                      \
    QDBusLockerBase::reportThreadAction(action, QDBusLockerBase::AfterAcquire, this); \
    } while (false)

# define SEM_RELEASE(action, sem)                                       \
    do {                                                                \
    QDBusLockerBase::reportThreadAction(action, QDBusLockerBase::BeforeRelease, that); \
    sem.release();                                                      \
    QDBusLockerBase::reportThreadAction(action, QDBusLockerBase::AfterRelease, that); \
    } while (false)

#else
# define SEM_ACQUIRE(action, sem)       sem.acquire()
# define SEM_RELEASE(action, sem)       sem.release()
#endif

#endif // QT_NO_DBUS
#endif
