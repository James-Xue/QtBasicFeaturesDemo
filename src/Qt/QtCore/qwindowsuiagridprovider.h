// Copyright (C) 2017 The Qt Company Ltd.


#ifndef QWINDOWSUIAGRIDPROVIDER_H
#define QWINDOWSUIAGRIDPROVIDER_H

#include <QtGui/qtguiglobal.h>
#if QT_CONFIG(accessibility)

#include "qwindowsuiabaseprovider.h"

QT_BEGIN_NAMESPACE

// Implements the Grid control pattern provider. Used by tables/trees.
class QWindowsUiaGridProvider : public QWindowsUiaBaseProvider, public QComObject<IGridProvider>
{
    Q_DISABLE_COPY_MOVE(QWindowsUiaGridProvider)
public:
    explicit QWindowsUiaGridProvider(QAccessible::Id id);
    virtual ~QWindowsUiaGridProvider();

    // IGridProvider
    HRESULT STDMETHODCALLTYPE GetItem(int row, int column, IRawElementProviderSimple **pRetVal) override;
    HRESULT STDMETHODCALLTYPE get_RowCount(int *pRetVal) override;
    HRESULT STDMETHODCALLTYPE get_ColumnCount(int *pRetVal) override;
};

QT_END_NAMESPACE

#endif // QT_CONFIG(accessibility)

#endif // QWINDOWSUIAGRIDPROVIDER_H
