// Copyright (C) 2021 The Qt Company Ltd.


#ifndef QEVENTDISPATCHER_WASM_P_H
#define QEVENTDISPATCHER_WASM_P_H

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

#include "qabstracteventdispatcher.h"
#include "private/qtimerinfo_unix_p.h"
#include <QtCore/qloggingcategory.h>
#include <QtCore/qwaitcondition.h>

#include <chrono>
#include <mutex>
#include <optional>
#include <tuple>

#include <emscripten/proxying.h>

QT_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(lcEventDispatcher);
Q_DECLARE_LOGGING_CATEGORY(lcEventDispatcherTimers)

class Q_CORE_EXPORT QEventDispatcherWasm : public QAbstractEventDispatcherV2
{
    Q_OBJECT
public:
    QEventDispatcherWasm();
    ~QEventDispatcherWasm();

    bool processEvents(QEventLoop::ProcessEventsFlags flags) override;

    void registerSocketNotifier(QSocketNotifier *notifier) override;
    void unregisterSocketNotifier(QSocketNotifier *notifier) override;

    void registerTimer(Qt::TimerId timerId, Duration interval, Qt::TimerType timerType,
                       QObject *object) override final;
    bool unregisterTimer(Qt::TimerId timerId) override final;
    bool unregisterTimers(QObject *object) override final;
    QList<TimerInfoV2> timersForObject(QObject *object) const override final;
    Duration remainingTime(Qt::TimerId timerId) const override final;

    void interrupt() override;
    void wakeUp() override;

    static void runOnMainThread(std::function<void(void)> fn);
    static void socketSelect(int timeout, int socket, bool waitForRead, bool waitForWrite,
                            bool *selectForRead, bool *selectForWrite, bool *socketDisconnect);

    static void registerStartupTask();
    static void completeStarupTask();
    static void callOnLoadedIfRequired();
    virtual void onLoaded();

protected:
    virtual bool processPostedEvents();

private:
    bool isMainThreadEventDispatcher();
    bool isSecondaryThreadEventDispatcher();
    static bool isValidEventDispatcherPointer(QEventDispatcherWasm *eventDispatcher);

    void handleApplicationExec();
    void handleDialogExec();
    bool wait(int timeout = -1);
    bool wakeEventDispatcherThread();
    static void callProcessPostedEvents(void *eventDispatcher);

    void processTimers();
    void updateNativeTimer();
    static void callProcessTimers(void *eventDispatcher);

    static void setEmscriptenSocketCallbacks();
    static void clearEmscriptenSocketCallbacks();
    static void socketError(int fd, int err, const char* msg, void *context);
    static void socketOpen(int fd, void *context);
    static void socketListen(int fd, void *context);
    static void socketConnection(int fd, void *context);
    static void socketMessage(int fd, void *context);
    static void socketClose(int fd, void *context);

    static void setSocketState(int socket, bool setReadyRead, bool setReadyWrite);
    static void clearSocketState(int socket);
    void waitForSocketState(int timeout, int socket, bool checkRead, bool checkWrite,
                            bool *selectForRead, bool *selectForWrite, bool *socketDisconnect);

    static void run(std::function<void(void)> fn);
    static void runAsync(std::function<void(void)> fn);
    static void runOnMainThreadAsync(std::function<void(void)> fn);

    static QEventDispatcherWasm *g_mainThreadEventDispatcher;

    bool m_interrupted = false;
    bool m_processTimers = false;
    bool m_pendingProcessEvents = false;

    QTimerInfoList *m_timerInfo = new QTimerInfoList();
    long m_timerId = 0;
    std::chrono::milliseconds m_timerTargetTime{};

#if QT_CONFIG(thread)
    std::mutex m_mutex;
    bool m_wakeUpCalled = false;
    std::condition_variable m_moreEvents;

    static QVector<QEventDispatcherWasm *> g_secondaryThreadEventDispatchers;
    static std::mutex g_staticDataMutex;
    static emscripten::ProxyingQueue g_proxyingQueue;
    static pthread_t g_mainThread;

    // Note on mutex usage: the global g_staticDataMutex protects the global (g_ prefixed) data,
    // while the per eventdispatcher m_mutex protects the state accociated with blocking and waking
    // that eventdispatcher thread. The locking order is g_staticDataMutex first, then m_mutex.
#endif

    static std::multimap<int, QSocketNotifier *> g_socketNotifiers;

    struct SocketReadyState {
        QEventDispatcherWasm *waiter = nullptr;
        bool waitForReadyRead = false;
        bool waitForReadyWrite = false;
        bool readyRead = false;
        bool readyWrite = false;
    };
    static std::map<int, SocketReadyState> g_socketState;
};

#endif // QEVENTDISPATCHER_WASM_P_H
