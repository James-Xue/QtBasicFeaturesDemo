// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QEVENTLOOP_P_H
#define QEVENTLOOP_P_H

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

#include "qcoreapplication.h"
#include <QtCore/private/qobject_p.h>

QT_BEGIN_NAMESPACE

class Q_AUTOTEST_EXPORT QEventLoopPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QEventLoop)
public:
    inline QEventLoopPrivate()
        : inExec(false)
    {
        returnCode.storeRelaxed(-1);
        exit.storeRelaxed(true);
    }
    ~QEventLoopPrivate() override;

    QAtomicInt quitLockRef;

    QBasicAtomicInt exit; // bool
    QBasicAtomicInt returnCode;
    bool inExec;

    void ref()
    {
        quitLockRef.ref();
    }

    void deref()
    {
        if (!quitLockRef.deref() && inExec) {
            qApp->postEvent(q_ptr, new QEvent(QEvent::Quit));
        }
    }
};

QT_END_NAMESPACE

#endif // QEVENTLOOP_P_H
