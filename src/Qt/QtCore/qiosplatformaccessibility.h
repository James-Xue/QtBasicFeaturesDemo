// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QIOSPLATFORMACCESSIBILITY_H
#define QIOSPLATFORMACCESSIBILITY_H

#include <qpa/qplatformaccessibility.h>

#if QT_CONFIG(accessibility)

QT_BEGIN_NAMESPACE

class QIOSPlatformAccessibility: public QPlatformAccessibility
{
public:
    QIOSPlatformAccessibility();
    ~QIOSPlatformAccessibility();

    virtual void notifyAccessibilityUpdate(QAccessibleEvent *event);
};

QT_END_NAMESPACE

#endif

#endif
