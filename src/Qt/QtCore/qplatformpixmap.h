// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QPLATFORMPIXMAP_H
#define QPLATFORMPIXMAP_H

//
//  W A R N I N G
//  -------------
//
// This file is part of the QPA API and is not meant to be used
// in applications. Usage of this API may make your code
// source and binary incompatible with future versions of Qt.
//

#include <QtGui/qtguiglobal.h>
#include <QtGui/qpixmap.h>
#include <QtCore/qatomic.h>

QT_BEGIN_NAMESPACE


class QImageReader;

class Q_GUI_EXPORT QPlatformPixmap
{
public:
    enum PixelType {
        // WARNING: Do not change the first two
        // Must match QPixmap::Type
        PixmapType, BitmapType
    };

    enum ClassId { RasterClass, DirectFBClass,
                   BlitterClass, Direct2DClass,
                   X11Class, CustomClass = 1024 };

    QPlatformPixmap(PixelType pixelType, int classId);
    virtual ~QPlatformPixmap();

    virtual QPlatformPixmap *createCompatiblePlatformPixmap() const;

    virtual void resize(int width, int height) = 0;
    virtual void fromImage(const QImage &image,
                           Qt::ImageConversionFlags flags) = 0;
    virtual void fromImageInPlace(QImage &image,
                                  Qt::ImageConversionFlags flags)
    {
        fromImage(image, flags);
    }

    virtual void fromImageReader(QImageReader *imageReader,
                                 Qt::ImageConversionFlags flags);

    virtual bool fromFile(const QString &filename, const char *format,
                          Qt::ImageConversionFlags flags);
    virtual bool fromData(const uchar *buffer, uint len, const char *format,
                          Qt::ImageConversionFlags flags);

    virtual void copy(const QPlatformPixmap *data, const QRect &rect);
    virtual bool scroll(int dx, int dy, const QRect &rect);

    virtual int metric(QPaintDevice::PaintDeviceMetric metric) const = 0;
    virtual void fill(const QColor &color) = 0;

    virtual QBitmap mask() const;
    virtual void setMask(const QBitmap &mask);

    virtual bool hasAlphaChannel() const = 0;
    virtual QPixmap transformed(const QTransform &matrix,
                                Qt::TransformationMode mode) const;

    virtual QImage toImage() const = 0;
    virtual QImage toImage(const QRect &rect) const;
    virtual QPaintEngine* paintEngine() const = 0;

    inline int serialNumber() const { return ser_no; }

    inline PixelType pixelType() const { return type; }
    inline ClassId classId() const { return static_cast<ClassId>(id); }

    virtual qreal devicePixelRatio() const = 0;
    virtual void setDevicePixelRatio(qreal scaleFactor) = 0;

    virtual QImage* buffer();

    inline int width() const { return w; }
    inline int height() const { return h; }
    inline int colorCount() const { return metric(QPaintDevice::PdmNumColors); }
    inline int depth() const { return d; }
    inline bool isNull() const { return is_null; }
    inline qint64 cacheKey() const {
        int classKey = id;
        if (classKey >= 1024)
            classKey = -(classKey >> 10);
        return ((((qint64) classKey) << 56)
                | (((qint64) ser_no) << 32)
                | ((qint64) detach_no));
    }

    static QPlatformPixmap *create(int w, int h, PixelType type);

protected:

    void setSerialNumber(int serNo);
    void setDetachNumber(int detNo);
    int w;
    int h;
    int d;
    bool is_null;

private:
    friend class QPixmap;
    friend class QX11PlatformPixmap;
    friend class QImagePixmapCleanupHooks; // Needs to set is_cached
    friend class QOpenGLTextureCache; //Needs to check the reference count
    friend class QExplicitlySharedDataPointer<QPlatformPixmap>;

    QAtomicInt ref;
    int detach_no;

    PixelType type;
    int id;
    int ser_no;
    uint is_cached;
};

#  define QT_XFORM_TYPE_MSBFIRST 0
#  define QT_XFORM_TYPE_LSBFIRST 1
Q_GUI_EXPORT bool qt_xForm_helper(const QTransform&, int, int, int, uchar*, qsizetype, int, int, const uchar*, qsizetype, int, int);

QT_END_NAMESPACE

#endif // QPLATFORMPIXMAP_H
