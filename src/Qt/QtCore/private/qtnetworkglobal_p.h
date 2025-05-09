// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QTNETWORKGLOBAL_P_H
#define QTNETWORKGLOBAL_P_H

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

#include <QtNetwork/qtnetworkglobal.h>
#include <QtCore/private/qglobal_p.h>
#include <QtNetwork/private/qtnetwork-config_p.h>

QT_BEGIN_NAMESPACE

enum {
#if defined(Q_OS_LINUX) || defined(Q_OS_QNX)
    PlatformSupportsAbstractNamespace = true
#else
    PlatformSupportsAbstractNamespace = false
#endif
};

QT_END_NAMESPACE
#endif // QTNETWORKGLOBAL_P_H
