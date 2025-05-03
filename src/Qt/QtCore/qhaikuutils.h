// Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Tobias Koenig <tobias.koenig@kdab.com>


#ifndef QHAIKUUTILS_H
#define QHAIKUUTILS_H

#include <QImage>

#include <GraphicsDefs.h>

QT_BEGIN_NAMESPACE

namespace QHaikuUtils
{
    color_space imageFormatToColorSpace(QImage::Format format);
    QImage::Format colorSpaceToImageFormat(color_space colorSpace);
}

QT_END_NAMESPACE

#endif
