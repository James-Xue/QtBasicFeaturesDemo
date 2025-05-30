// Copyright (C) 2019 The Qt Company Ltd.


#ifndef QCOCOAWINDOWMANAGER_H
#define QCOCOAWINDOWMANAGER_H

#include <QtCore/qglobal.h>
#include <QtCore/private/qcore_mac_p.h>

QT_BEGIN_NAMESPACE

class QCocoaWindowManager
{
public:
    QCocoaWindowManager();

private:

    QMacNotificationObserver m_applicationDidFinishLaunchingObserver;
    void initialize();

    QMacKeyValueObserver m_modalSessionObserver;
    void modalSessionChanged();
};

QT_END_NAMESPACE

#endif // QCOCOAWINDOWMANAGER_H
