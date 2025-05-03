// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QTESTSPONTANEEVENT_H
#define QTESTSPONTANEEVENT_H

#include <QtCore/qcoreevent.h>

#if 0
// inform syncqt
#pragma qt_no_master_include
#endif

QT_BEGIN_NAMESPACE

class QSpontaneKeyEvent
{
public:
    static inline void setSpontaneous(QEvent *ev)
    {
        ev->setSpontaneous();
    }
};

QT_END_NAMESPACE

#endif
