// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QTDEPRECATIONDEFINITIONS_H
#define QTDEPRECATIONDEFINITIONS_H

#ifndef QT_DISABLE_DEPRECATED_UP_TO
    // If the deprecated macro is defined, use its value
    #ifdef QT_DISABLE_DEPRECATED_BEFORE
        #define QT_DISABLE_DEPRECATED_UP_TO QT_DISABLE_DEPRECATED_BEFORE
    #else
        #define QT_DISABLE_DEPRECATED_UP_TO 0x040800
    #endif
#endif

#if QT_DISABLE_DEPRECATED_UP_TO < 0x040800
    #warning QT_DISABLE_DEPRECATED_UP_TO is set to the version that is lower than the version that \
           Qt was built with. This may lead to linking issues.
#endif

#ifndef QT_WARN_DEPRECATED_UP_TO
    // If the deprecated macro is defined, use its value
    #ifdef QT_DEPRECATED_WARNINGS_SINCE
        #define QT_WARN_DEPRECATED_UP_TO QT_DEPRECATED_WARNINGS_SINCE
    #else
        #define QT_WARN_DEPRECATED_UP_TO 0x070000
    #endif
#endif

#endif // QTDEPRECATIONDEFINITIONS_H
