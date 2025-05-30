// Copyright (C) 2017 The Qt Company Ltd.


#ifndef QWINDOWSUIAACCESSIBILITY_H
#define QWINDOWSUIAACCESSIBILITY_H

#include <QtGui/qtguiglobal.h>
#if QT_CONFIG(accessibility)

#include <QtCore/qt_windows.h>
#include "qwindowscontext.h"
#include <qpa/qplatformaccessibility.h>

QT_BEGIN_NAMESPACE

// Windows platform accessibility implemented over UI Automation.
class QWindowsUiaAccessibility : public QPlatformAccessibility
{
public:
    explicit QWindowsUiaAccessibility();
    virtual ~QWindowsUiaAccessibility();
    static bool handleWmGetObject(HWND hwnd, WPARAM wParam, LPARAM lParam, LRESULT *lResult);
    void notifyAccessibilityUpdate(QAccessibleEvent *event) override;
private:
    static bool m_accessibleActive;
};

QT_END_NAMESPACE

#endif // QT_CONFIG(accessibility)

#endif // QWINDOWSUIAACCESSIBILITY_H
