// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QWINDOWSDIRECT2DNATIVEINTERFACE_H
#define QWINDOWSDIRECT2DNATIVEINTERFACE_H

#include "qwindowsnativeinterface.h"

QT_BEGIN_NAMESPACE

class QWindowsDirect2DNativeInterface : public QWindowsNativeInterface
{
    Q_OBJECT
public:
    void *nativeResourceForBackingStore(const QByteArray &resource, QBackingStore *bs) override;
};

QT_END_NAMESPACE

#endif // QWINDOWSDIRECT2DNATIVEINTERFACE_H
