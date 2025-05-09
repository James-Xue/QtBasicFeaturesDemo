// Copyright (C) 2021 The Qt Company Ltd.


#ifndef QDTLS_OPENSSL_P_H
#define QDTLS_OPENSSL_P_H

#include <QtNetwork/private/qtnetworkglobal_p.h>

#include "qsslcontext_openssl_p.h"
#include "qtlsbackend_openssl_p.h"
#include "qtls_openssl_p.h"
#include "qopenssl_p.h"

#include "../shared/qdtls_base_p.h"

#include <QtNetwork/private/qdtls_p.h>

#include <QtNetwork/qsslpresharedkeyauthenticator.h>
#include <QtNetwork/qhostaddress.h>

#include <QtCore/qsharedpointer.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qglobal.h>
#include <QtCore/qlist.h>

#include <openssl/ossl_typ.h>

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

QT_REQUIRE_CONFIG(openssl);
QT_REQUIRE_CONFIG(dtls);

QT_BEGIN_NAMESPACE

class QDtlsPrivateOpenSSL;
class QDtlsBasePrivate;
class QUdpSocket;

namespace dtlsopenssl
{

class DtlsState
{
public:
    // Note, bioMethod _must_ outlive BIOs it was used to create. Thus
    // the order of declarations here matters.
    using BioMethod = QSharedPointer<BIO_METHOD>;
    BioMethod bioMethod;

    using TlsContext = std::shared_ptr<QSslContext>;
    TlsContext tlsContext;

    using TlsConnection = QSharedPointer<SSL>;
    TlsConnection tlsConnection;

    QByteArray dgram;

    QHostAddress remoteAddress;
    quint16 remotePort = 0;

    QList<QSslErrorEntry> x509Errors;

    long peeking = false;
    QUdpSocket *udpSocket = nullptr;
    bool writeSuppressed = false;

    bool init(QDtlsBasePrivate *dtlsBase, QUdpSocket *socket,
              const QHostAddress &remote, quint16 port,
              const QByteArray &receivedMessage);

    void reset();

    QDtlsPrivateOpenSSL *dtlsPrivate = nullptr;
    QByteArray secret;

#ifdef QT_CRYPTOGRAPHICHASH_ONLY_SHA1
    QCryptographicHash::Algorithm hashAlgorithm = QCryptographicHash::Sha1;
#else
    QCryptographicHash::Algorithm hashAlgorithm = QCryptographicHash::Sha256;
#endif

private:

    bool initTls(QDtlsBasePrivate *dtlsBase);
    bool initCtxAndConnection(QDtlsBasePrivate *dtlsBase);
    bool initBIO(QDtlsBasePrivate *dtlsBase);
    void setLinkMtu(QDtlsBasePrivate *dtlsBase);
};

} // namespace dtlsopenssl

// The trick with 'right' ancestor in the tree overriding (only once) some shared
// virtual functions is intentional. Too bad MSVC warns me about ... exactly the
// feature of C++ that I want to use.

QT_WARNING_PUSH
QT_WARNING_DISABLE_MSVC(4250)

class QDtlsClientVerifierOpenSSL : public QTlsPrivate::DtlsCookieVerifier, public QDtlsBasePrivate
{
public:
    QDtlsClientVerifierOpenSSL();

    bool verifyClient(QUdpSocket *socket, const QByteArray &dgram,
                      const QHostAddress &address, quint16 port) override;
    QByteArray verifiedHello() const override;

private:
    dtlsopenssl::DtlsState dtls;
    QByteArray verifiedClientHello;
};

class QDtlsPrivateOpenSSL : public QTlsPrivate::DtlsCryptograph, public QDtlsBasePrivate
{
public:

    QDtlsPrivateOpenSSL(QDtls *qObject, QSslSocket::SslMode mode);

private:

    QSslSocket::SslMode cryptographMode() const override;
    void setPeer(const QHostAddress &addr, quint16 port, const QString &name) override;
    QHostAddress peerAddress() const override;
    quint16 peerPort() const override;
    void setPeerVerificationName(const QString &name) override;
    QString peerVerificationName() const override;

    virtual void setDtlsMtuHint(quint16 mtu) override;
    virtual quint16 dtlsMtuHint() const override;

    virtual QDtls::HandshakeState state() const override;
    virtual bool isConnectionEncrypted() const override;

    bool startHandshake(QUdpSocket *socket, const QByteArray &datagram) override;
    bool continueHandshake(QUdpSocket *socket, const QByteArray &datagram) override;
    bool resumeHandshake(QUdpSocket *socket) override;
    void abortHandshake(QUdpSocket *socket) override;
    bool handleTimeout(QUdpSocket *socket) override;
    void sendShutdownAlert(QUdpSocket *socket) override;

    QList<QSslError> peerVerificationErrors() const override;
    void ignoreVerificationErrors(const QList<QSslError> &errorsToIgnore) override;

    QSslCipher dtlsSessionCipher() const override;
    QSsl::SslProtocol dtlsSessionProtocol() const override;

    qint64 writeDatagramEncrypted(QUdpSocket *socket, const QByteArray &datagram) override;
    QByteArray decryptDatagram(QUdpSocket *socket, const QByteArray &tlsdgram) override;

public:
    unsigned pskClientCallback(const char *hint, char *identity, unsigned max_identity_len,
                               unsigned char *psk, unsigned max_psk_len);
    unsigned pskServerCallback(const char *identity, unsigned char *psk,
                               unsigned max_psk_len);

private:

    bool verifyPeer();
    void storePeerCertificates();
    bool tlsErrorsWereIgnored() const;
    void fetchNegotiatedParameters();
    void reportTimeout();
    void resetDtls();

    QList<QSslErrorEntry> opensslErrors;
    dtlsopenssl::DtlsState dtls;

    // We have to externally handle timeouts since we have non-blocking
    // sockets and OpenSSL(DTLS) with non-blocking UDP sockets does not
    // know if a timeout has occurred.
    struct TimeoutHandler : QObject
    {
        TimeoutHandler() = default;

        void start(int hintMs = 0);
        void doubleTimeout();
        void resetTimeout() {timeoutMs = 1000;}
        void stop();
        void timerEvent(QTimerEvent *event) override;

        int timerId = -1;
        int timeoutMs = 1000;

        QDtlsPrivateOpenSSL *dtlsConnection = nullptr;
    };

    QDtls *q = nullptr;
    QDtls::HandshakeState handshakeState = QDtls::HandshakeNotStarted;

    QList<QSslError> tlsErrors;
    QList<QSslError> tlsErrorsToIgnore;
    bool connectionEncrypted = false;
    // We will initialize it 'lazily', just in case somebody wants to move
    // QDtls to another thread.
    QScopedPointer<TimeoutHandler> timeoutHandler;
    bool connectionWasShutdown = false;
    QSslPreSharedKeyAuthenticator pskAuthenticator;
    QByteArray identityHint;
};

QT_WARNING_POP // C4250

QT_END_NAMESPACE

#endif // QDTLS_OPENSSL_P_H
