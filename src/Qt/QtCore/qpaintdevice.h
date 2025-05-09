// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QPAINTDEVICE_H
#define QPAINTDEVICE_H

#include <QtGui/qtguiglobal.h>
#include <QtGui/qwindowdefs.h>
#include <QtCore/qrect.h>

QT_BEGIN_NAMESPACE



class QPaintEngine;

class Q_GUI_EXPORT QPaintDevice                                // device for QPainter
{
public:
    enum PaintDeviceMetric {
        PdmWidth = 1,
        PdmHeight,
        PdmWidthMM,
        PdmHeightMM,
        PdmNumColors,
        PdmDepth,
        PdmDpiX,
        PdmDpiY,
        PdmPhysicalDpiX,
        PdmPhysicalDpiY,
        PdmDevicePixelRatio,
        PdmDevicePixelRatioScaled,
        PdmDevicePixelRatioF_EncodedA,
        PdmDevicePixelRatioF_EncodedB,
    };

    virtual ~QPaintDevice();

    virtual int devType() const;
    bool paintingActive() const;
    virtual QPaintEngine *paintEngine() const = 0;

    int width() const { return metric(PdmWidth); }
    int height() const { return metric(PdmHeight); }
    int widthMM() const { return metric(PdmWidthMM); }
    int heightMM() const { return metric(PdmHeightMM); }
    int logicalDpiX() const { return metric(PdmDpiX); }
    int logicalDpiY() const { return metric(PdmDpiY); }
    int physicalDpiX() const { return metric(PdmPhysicalDpiX); }
    int physicalDpiY() const { return metric(PdmPhysicalDpiY); }
    qreal devicePixelRatio() const;
    qreal devicePixelRatioF()  const { return devicePixelRatio(); }
    int colorCount() const { return metric(PdmNumColors); }
    int depth() const { return metric(PdmDepth); }

    static inline qreal devicePixelRatioFScale() { return 0x10000; }
    static inline int encodeMetricF(PaintDeviceMetric metric, double value);
protected:
    QPaintDevice() noexcept;
    virtual int metric(PaintDeviceMetric metric) const;
    virtual void initPainter(QPainter *painter) const;
    virtual QPaintDevice *redirected(QPoint *offset) const;
    virtual QPainter *sharedPainter() const;
    double getDecodedMetricF(PaintDeviceMetric metricA, PaintDeviceMetric metricB) const;

    ushort        painters;                        // refcount
private:
    Q_DISABLE_COPY(QPaintDevice)

    friend class QPainter;
    friend class QPainterPrivate;
    friend class QFontEngineMac;
    friend class QX11PaintEngine;
    friend Q_GUI_EXPORT int qt_paint_device_metric(const QPaintDevice *device, PaintDeviceMetric metric);
};

/*****************************************************************************
  Inline functions
 *****************************************************************************/

inline int QPaintDevice::devType() const
{ return QInternal::UnknownDevice; }

inline bool QPaintDevice::paintingActive() const
{ return painters != 0; }

inline int QPaintDevice::encodeMetricF(PaintDeviceMetric metric, double value)
{
    qint32 buf[2];
    Q_STATIC_ASSERT(sizeof(buf) == sizeof(double));
    memcpy(buf, &value, sizeof(buf));
    return buf[metric & 1];
}

QT_END_NAMESPACE

#endif // QPAINTDEVICE_H
