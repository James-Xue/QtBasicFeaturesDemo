// Copyright (C) 2021 The Qt Company Ltd.


#ifndef QTLSBACKEND_ST_P_H
#define QTLSBACKEND_ST_P_H

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

#include <QtNetwork/private/qtnetworkglobal_p.h>

#include <QtNetwork/private/qtlsbackend_p.h>

#include <QtCore/qglobal.h>


QT_BEGIN_NAMESPACE

class QSecureTransportBackend : public QTlsBackend
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QTlsBackend_iid)
    Q_INTERFACES(QTlsBackend)

private:

    QString tlsLibraryVersionString() const override;
    virtual QString tlsLibraryBuildVersionString() const override;
    virtual void ensureInitialized() const override;

    QString backendName() const override;

    QList<QSsl::SslProtocol> supportedProtocols() const override;
    QList<QSsl::SupportedFeature> supportedFeatures() const override;
    QList<QSsl::ImplementedClass> implementedClasses() const override;

    QTlsPrivate::TlsKey *createKey() const override;
    QTlsPrivate::X509Certificate *createCertificate() const override;

    QList<QSslCertificate> systemCaCertificates() const override;

    QTlsPrivate::X509PemReaderPtr X509PemReader() const override;
    QTlsPrivate::X509DerReaderPtr X509DerReader() const override;

    QTlsPrivate::TlsCryptograph *createTlsCryptograph() const override;

    static bool s_loadedCiphersAndCerts;
};

Q_DECLARE_LOGGING_CATEGORY(lcSecureTransport)

QT_END_NAMESPACE

#endif // QTLSBACKEND_ST_P_H


