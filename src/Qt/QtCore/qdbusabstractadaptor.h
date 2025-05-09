// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QDBUSABSTRACTADAPTOR_H
#define QDBUSABSTRACTADAPTOR_H

#include <QtDBus/qtdbusglobal.h>
#include <QtCore/qobject.h>

#ifndef QT_NO_DBUS

QT_BEGIN_NAMESPACE


class QDBusAbstractAdaptorPrivate;
class Q_DBUS_EXPORT QDBusAbstractAdaptor: public QObject
{
    Q_OBJECT
protected:
    explicit QDBusAbstractAdaptor(QObject *parent);

public:
    ~QDBusAbstractAdaptor();

protected:
    void setAutoRelaySignals(bool enable);
    bool autoRelaySignals() const;

private:
    Q_DECLARE_PRIVATE(QDBusAbstractAdaptor)
};

QT_END_NAMESPACE

#endif // QT_NO_DBUS

#endif
