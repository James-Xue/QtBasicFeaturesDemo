// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QDBUSSERVER_H
#define QDBUSSERVER_H

#include <QtDBus/qtdbusglobal.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>

#ifndef QT_NO_DBUS

QT_BEGIN_NAMESPACE


class QDBusConnectionPrivate;
class QDBusError;
class QDBusConnection;

class Q_DBUS_EXPORT QDBusServer: public QObject
{
    Q_OBJECT
public:
    explicit QDBusServer(const QString &address, QObject *parent = nullptr);
    explicit QDBusServer(QObject *parent = nullptr);
    virtual ~QDBusServer();

    bool isConnected() const;
    QDBusError lastError() const;
    QString address() const;

    void setAnonymousAuthenticationAllowed(bool value);
    bool isAnonymousAuthenticationAllowed() const;

Q_SIGNALS:
    void newConnection(const QDBusConnection &connection);

private:
    Q_DISABLE_COPY(QDBusServer)
    QDBusConnectionPrivate *d;
    friend class QDBusConnectionPrivate;
};

QT_END_NAMESPACE

#endif // QT_NO_DBUS
#endif
