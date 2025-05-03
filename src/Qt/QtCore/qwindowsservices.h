// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QWINDOWSDESKTOPSERVICES_H
#define QWINDOWSDESKTOPSERVICES_H

#include <qpa/qplatformservices.h>

QT_BEGIN_NAMESPACE

class QWindowsServices : public QPlatformServices
{
public:
    bool openUrl(const QUrl &url) override;
    bool openDocument(const QUrl &url) override;
};

QT_END_NAMESPACE

#endif // QWINDOWSDESKTOPSERVICES_H
