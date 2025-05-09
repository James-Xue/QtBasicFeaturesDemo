// Copyright (C) 2020 The Qt Company Ltd.


#ifndef QWINDOWSUIAEXPANDCOLLAPSEPROVIDER_H
#define QWINDOWSUIAEXPANDCOLLAPSEPROVIDER_H

#include <QtGui/qtguiglobal.h>
#if QT_CONFIG(accessibility)

#include "qwindowsuiabaseprovider.h"

QT_BEGIN_NAMESPACE

// Implements the Expand/Collapse control pattern provider. Used for menu items with submenus.
class QWindowsUiaExpandCollapseProvider : public QWindowsUiaBaseProvider,
                                          public QComObject<IExpandCollapseProvider>
{
    Q_DISABLE_COPY_MOVE(QWindowsUiaExpandCollapseProvider)
public:
    explicit QWindowsUiaExpandCollapseProvider(QAccessible::Id id);
    virtual ~QWindowsUiaExpandCollapseProvider() override;

    // IExpandCollapseProvider
    HRESULT STDMETHODCALLTYPE Expand() override;
    HRESULT STDMETHODCALLTYPE Collapse() override;
    HRESULT STDMETHODCALLTYPE get_ExpandCollapseState(__RPC__out ExpandCollapseState *pRetVal) override;
};

QT_END_NAMESPACE

#endif // QT_CONFIG(accessibility)

#endif // QWINDOWSUIAEXPANDCOLLAPSEPROVIDER_H
