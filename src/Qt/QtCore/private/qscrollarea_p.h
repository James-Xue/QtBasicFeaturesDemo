// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QSCROLLAREA_P_H
#define QSCROLLAREA_P_H

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

#include <QtWidgets/private/qtwidgetsglobal_p.h>

#include "private/qabstractscrollarea_p.h"
#include <QtWidgets/qscrollbar.h>

#include <QtCore/qpointer.h>

QT_REQUIRE_CONFIG(scrollarea);

QT_BEGIN_NAMESPACE

class QScrollAreaPrivate: public QAbstractScrollAreaPrivate
{
    Q_DECLARE_PUBLIC(QScrollArea)

public:
    QScrollAreaPrivate(): resizable(false) {}
    void updateScrollBars();
    void updateWidgetPosition();
    QPointer<QWidget> widget;
    mutable QSize widgetSize;
    bool resizable;
    Qt::Alignment alignment;
};

QT_END_NAMESPACE

#endif
