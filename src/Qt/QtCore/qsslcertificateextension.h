// Copyright (C) 2011 Richard J. Moore <rich@kde.org>


#ifndef QSSLCERTIFICATEEXTENSION_H
#define QSSLCERTIFICATEEXTENSION_H

#include <QtNetwork/qtnetworkglobal.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qshareddata.h>
#include <QtCore/qstring.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE

class QSslCertificateExtensionPrivate;

class Q_NETWORK_EXPORT QSslCertificateExtension
{
public:
    QSslCertificateExtension();
    QSslCertificateExtension(const QSslCertificateExtension &other);
    QSslCertificateExtension &operator=(QSslCertificateExtension &&other) noexcept { swap(other); return *this; }
    QSslCertificateExtension &operator=(const QSslCertificateExtension &other);
    ~QSslCertificateExtension();

    void swap(QSslCertificateExtension &other) noexcept { d.swap(other.d); }

    QString oid() const;
    QString name() const;
    QVariant value() const;
    bool isCritical() const;

    bool isSupported() const;

private:
    friend class QSslCertificatePrivate;
    QSharedDataPointer<QSslCertificateExtensionPrivate> d;
};

Q_DECLARE_SHARED(QSslCertificateExtension)

QT_END_NAMESPACE


#endif // QSSLCERTIFICATEEXTENSION_H


