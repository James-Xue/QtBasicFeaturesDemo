// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QMOVIE_H
#define QMOVIE_H

#include <QtGui/qtguiglobal.h>

#include <QtCore/qobject.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qlist.h>
#include <QtGui/qimagereader.h>

QT_REQUIRE_CONFIG(movie);

QT_BEGIN_NAMESPACE

class QByteArray;
class QColor;
class QIODevice;
class QImage;
class QPixmap;
class QRect;
class QSize;

class QMoviePrivate;
class Q_GUI_EXPORT QMovie : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QMovie)
    Q_PROPERTY(int speed READ speed WRITE setSpeed BINDABLE bindableSpeed)
    Q_PROPERTY(CacheMode cacheMode READ cacheMode WRITE setCacheMode BINDABLE bindableCacheMode)
public:
    enum MovieState {
        NotRunning,
        Paused,
        Running
    };
    Q_ENUM(MovieState)
    enum CacheMode {
        CacheNone,
        CacheAll
    };
    Q_ENUM(CacheMode)

    explicit QMovie(QObject *parent = nullptr);
    explicit QMovie(QIODevice *device, const QByteArray &format = QByteArray(), QObject *parent = nullptr);
    explicit QMovie(const QString &fileName, const QByteArray &format = QByteArray(), QObject *parent = nullptr);
    ~QMovie();

    static QList<QByteArray> supportedFormats();

    void setDevice(QIODevice *device);
    QIODevice *device() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

    void setFormat(const QByteArray &format);
    QByteArray format() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    MovieState state() const;

    QRect frameRect() const;
    QImage currentImage() const;
    QPixmap currentPixmap() const;

    bool isValid() const;
    QImageReader::ImageReaderError lastError() const;
    QString lastErrorString() const;

    bool jumpToFrame(int frameNumber);
    int loopCount() const;
    int frameCount() const;
    int nextFrameDelay() const;
    int currentFrameNumber() const;

    int speed() const;
    QBindable<int> bindableSpeed();

    QSize scaledSize();
    void setScaledSize(const QSize &size);

    CacheMode cacheMode() const;
    void setCacheMode(CacheMode mode);
    QBindable<CacheMode> bindableCacheMode();

Q_SIGNALS:
    void started();
    void resized(const QSize &size);
    void updated(const QRect &rect);
    void stateChanged(QMovie::MovieState state);
    void error(QImageReader::ImageReaderError error);
    void finished();
    void frameChanged(int frameNumber);

public Q_SLOTS:
    void start();
    bool jumpToNextFrame();
    void setPaused(bool paused);
    void stop();
    void setSpeed(int percentSpeed);

private:
    Q_DISABLE_COPY(QMovie)
    Q_PRIVATE_SLOT(d_func(), void _q_loadNextFrame())
};

QT_END_NAMESPACE

#endif // QMOVIE_H
