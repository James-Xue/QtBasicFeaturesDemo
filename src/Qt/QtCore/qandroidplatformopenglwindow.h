// Copyright (C) 2014 BogDan Vatra <bogdan@kde.org>
// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QANDROIDPLATFORMOPENGLWINDOW_H
#define QANDROIDPLATFORMOPENGLWINDOW_H

#include "qandroidplatformwindow.h"

#include <QWaitCondition>
#include <QtCore/qjnienvironment.h>
#include <QtCore/qjniobject.h>

#include <EGL/egl.h>

QT_BEGIN_NAMESPACE

class QAndroidPlatformOpenGLWindow : public QAndroidPlatformWindow
{
public:
    explicit QAndroidPlatformOpenGLWindow(QWindow *window, EGLDisplay display);
    ~QAndroidPlatformOpenGLWindow();

    void setGeometry(const QRect &rect) override;
    EGLSurface eglSurface(EGLConfig config);
    QSurfaceFormat format() const override;

    bool checkNativeSurface(EGLConfig config);

    void applicationStateChanged(Qt::ApplicationState) override;

protected:
    void createEgl(EGLConfig config);
    void clearSurface() override;

private:
    EGLDisplay m_eglDisplay = EGL_NO_DISPLAY;
    EGLSurface m_eglSurface = EGL_NO_SURFACE;
    EGLNativeWindowType m_nativeWindow = nullptr;

    QSurfaceFormat m_format;
};

QT_END_NAMESPACE
#endif // QANDROIDPLATFORMOPENGLWINDOW_H
