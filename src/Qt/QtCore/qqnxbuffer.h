// Copyright (C) 2011 - 2012 Research In Motion


#ifndef QQNXBUFFER_H
#define QQNXBUFFER_H

#include <QtGui/QImage>
#include <QtCore/QLoggingCategory>

#include <screen/screen.h>

QT_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(lcQpaScreenBuffer)

class QQnxBuffer
{
public:
    QQnxBuffer();
    QQnxBuffer(screen_buffer_t buffer);
    QQnxBuffer(const QQnxBuffer &other);
    virtual ~QQnxBuffer();

    screen_buffer_t nativeBuffer() const { return m_buffer; }
    const QImage *image() const { return (m_buffer != nullptr) ? &m_image : nullptr; }
    QImage *image() { return (m_buffer != nullptr) ? &m_image : nullptr; }

    QRect rect() const { return m_image.rect(); }

    void invalidateInCache();

private:
    screen_buffer_t m_buffer;
    QImage m_image;
};

QT_END_NAMESPACE

#endif // QQNXBUFFER_H
