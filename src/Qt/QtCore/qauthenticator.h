// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QAUTHENTICATOR_H
#define QAUTHENTICATOR_H

#include <QtNetwork/qtnetworkglobal.h>
#include <QtCore/qstring.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE


class QAuthenticatorPrivate;
class QUrl;

class Q_NETWORK_EXPORT QAuthenticator
{
    Q_GADGET
public:
    QAuthenticator();
    ~QAuthenticator();

    QAuthenticator(const QAuthenticator &other);
    QAuthenticator &operator=(const QAuthenticator &other);

    bool operator==(const QAuthenticator &other) const;
    inline bool operator!=(const QAuthenticator &other) const { return !operator==(other); }

    QString user() const;
    void setUser(const QString &user);

    QString password() const;
    void setPassword(const QString &password);

    QString realm() const;
    void setRealm(const QString &realm);

    QVariant option(const QString &opt) const;
    QVariantHash options() const;
    void setOption(const QString &opt, const QVariant &value);

    bool isNull() const;
    void detach();
private:
    friend class QAuthenticatorPrivate;
    QAuthenticatorPrivate *d;
};

QT_END_NAMESPACE

#endif
