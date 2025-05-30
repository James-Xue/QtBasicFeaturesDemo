// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QPLATFORMGRAPHICSBUFFERHELPER_H
#define QPLATFORMGRAPHICSBUFFERHELPER_H

#include <QtGui/qtguiglobal.h>
#include <QtGui/qpa/qplatformgraphicsbuffer.h>

QT_BEGIN_NAMESPACE

namespace QPlatformGraphicsBufferHelper {
    Q_GUI_EXPORT bool lockAndBindToTexture(QPlatformGraphicsBuffer *graphicsBuffer, bool *swizzleRandB, bool *premultipliedB, const QRect &rect = QRect());
    bool bindSWToTexture(const QPlatformGraphicsBuffer *graphicsBuffer, bool *swizzleRandB = nullptr, bool *premultipliedB = nullptr, const QRect &rect = QRect());
}

QT_END_NAMESPACE

#endif
