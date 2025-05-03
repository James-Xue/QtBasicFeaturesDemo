// Copyright (C) 2016 Pelagicore AG


#ifndef QEGLFSKMSEGLDEVICESCREEN_H
#define QEGLFSKMSEGLDEVICESCREEN_H

#include <private/qeglfskmsscreen_p.h>

QT_BEGIN_NAMESPACE

class QEglFSKmsEglDeviceScreen : public QEglFSKmsScreen
{
public:
    QEglFSKmsEglDeviceScreen(QEglFSKmsDevice *device, const QKmsOutput &output);
    ~QEglFSKmsEglDeviceScreen();

    QPlatformCursor *cursor() const override;

    void waitForFlip() override;
private:
    uint32_t m_default_fb_handle;
    uint32_t m_default_fb_id;
};

QT_END_NAMESPACE

#endif // QEGLFSKMSEGLDEVICESCREEN_H
