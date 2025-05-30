// Copyright (C) 2014 BogDan Vatra <bogdan@kde.org>
// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QANDROIDPLATFORMSCREEN_H
#define QANDROIDPLATFORMSCREEN_H

#include <QList>
#include <QPainter>
#include <QTimer>
#include <QWaitCondition>
#include <QtCore/QJniObject>
#include <qpa/qplatformscreen.h>
#include <QtGui/qscreen_platform.h>

QT_BEGIN_NAMESPACE

class QAndroidPlatformWindow;


class QAndroidPlatformScreen : public QObject,
                               public QPlatformScreen,
                               public QNativeInterface::QAndroidScreen
{
    Q_OBJECT
public:
    QAndroidPlatformScreen(const QJniObject &displayObject);
    ~QAndroidPlatformScreen();

    QRect geometry() const override { return QRect(QPoint(), m_size); }
    QRect availableGeometry() const override { return m_availableGeometry; }
    int depth() const override { return m_depth; }
    QImage::Format format() const override { return m_format; }
    QSizeF physicalSize() const override { return m_physicalSize; }

    QString name() const override { return m_name; }
    QList<Mode> modes() const override { return m_modes; }
    int currentMode() const override { return m_currentMode; }
    int preferredMode() const override { return m_currentMode; }
    qreal refreshRate() const override { return m_refreshRate; }
    inline QWindow *topVisibleWindow() const;
    QWindow *topLevelAt(const QPoint & p) const override;

    void addWindow(QAndroidPlatformWindow *window);
    void removeWindow(QAndroidPlatformWindow *window);
    void raise(QAndroidPlatformWindow *window);
    void lower(QAndroidPlatformWindow *window);
    void topVisibleWindowChanged();
    int displayId() const override;

public slots:
    void setPhysicalSize(const QSize &size);
    void setAvailableGeometry(const QRect &rect);
    void setSize(const QSize &size);
    void setSizeParameters(const QSize &physicalSize, const QSize &size,
                           const QRect &availableGeometry);
    void setRefreshRate(qreal refreshRate);
    void setOrientation(Qt::ScreenOrientation orientation);

protected:
    typedef QList<QAndroidPlatformWindow *> WindowStackType;
    WindowStackType m_windowStack;
    QRect m_availableGeometry;
    int m_depth;
    QImage::Format m_format;
    QSizeF m_physicalSize;
    qreal m_refreshRate;
    QString m_name;
    QList<Mode> m_modes;
    int m_currentMode = 0;
    int m_displayId = -1;

private:
    QDpi logicalDpi() const override;
    QDpi logicalBaseDpi() const override;
    Qt::ScreenOrientation orientation() const override;
    Qt::ScreenOrientation nativeOrientation() const override;
    void applicationStateChanged(Qt::ApplicationState);
private:
    QSize m_size;
};

QT_END_NAMESPACE
#endif
