// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QEGLFSVIVINTEGRATION_H
#define QEGLFSVIVINTEGRATION_H

#include "private/qeglfsdeviceintegration_p.h"

QT_BEGIN_NAMESPACE

class QEglFSVivIntegration : public QEglFSDeviceIntegration
{
public:
    void platformInit() override;
    QSize screenSize() const override;
    EGLNativeWindowType createNativeWindow(QPlatformWindow *window, const QSize &size, const QSurfaceFormat &format) override;
    void destroyNativeWindow(EGLNativeWindowType window) override;
    EGLNativeDisplayType platformDisplay() const override;

private:
    QSize mScreenSize;
    EGLNativeDisplayType mNativeDisplay;
};

QT_END_NAMESPACE

#endif
