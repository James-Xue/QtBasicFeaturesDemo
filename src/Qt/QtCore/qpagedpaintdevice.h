// Copyright (C) 2020 The Qt Company Ltd.


#ifndef QPAGEDPAINTDEVICE_H
#define QPAGEDPAINTDEVICE_H

#include <QtGui/qtguiglobal.h>
#include <QtGui/qpaintdevice.h>
#include <QtGui/qpagelayout.h>
#include <QtGui/qpageranges.h>

QT_BEGIN_NAMESPACE

#if defined(B0)
#undef B0 // Terminal hang-up.  We assume that you do not want that.
#endif

class QPagedPaintDevicePrivate;

class Q_GUI_EXPORT QPagedPaintDevice : public QPaintDevice
{
public:
    ~QPagedPaintDevice();

    virtual bool newPage() = 0;

    // keep in sync with QPdfEngine::PdfVersion!
    enum PdfVersion {
        PdfVersion_1_4,
        PdfVersion_A1b,
        PdfVersion_1_6,
        PdfVersion_X4,
    };

    virtual bool setPageLayout(const QPageLayout &pageLayout);
    virtual bool setPageSize(const QPageSize &pageSize);
    virtual bool setPageOrientation(QPageLayout::Orientation orientation);
    virtual bool setPageMargins(const QMarginsF &margins, QPageLayout::Unit units = QPageLayout::Millimeter);
    QPageLayout pageLayout() const;

    virtual void setPageRanges(const QPageRanges &ranges);
    QPageRanges pageRanges() const;

protected:
    QPagedPaintDevice(QPagedPaintDevicePrivate *dd);
    QPagedPaintDevicePrivate *dd();
    friend class QPagedPaintDevicePrivate;
    QPagedPaintDevicePrivate *d;
};

QT_END_NAMESPACE

#endif
