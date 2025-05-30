// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QJPEGHANDLER_P_H
#define QJPEGHANDLER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/qimageiohandler.h>
#include <QtCore/QSize>
#include <QtCore/QRect>

QT_BEGIN_NAMESPACE

class QJpegHandlerPrivate;
class QJpegHandler : public QImageIOHandler
{
public:
    QJpegHandler();
    ~QJpegHandler();

    bool canRead() const override;
    bool read(QImage *image) override;
    bool write(const QImage &image) override;

    static bool canRead(QIODevice *device);

    QVariant option(ImageOption option) const override;
    void setOption(ImageOption option, const QVariant &value) override;
    bool supportsOption(ImageOption option) const override;

private:
    QJpegHandlerPrivate *d;
};

QT_END_NAMESPACE

#endif // QJPEGHANDLER_P_H
