// Copyright (C) 2021 The Qt Company Ltd.


#ifndef QTLSKEY_ST_P_H
#define QTLSKEY_ST_P_H

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

#include "../shared/qtlskey_generic_p.h"

#include <QtCore/qglobal.h>

QT_REQUIRE_CONFIG(ssl);

QT_BEGIN_NAMESPACE

namespace QTlsPrivate {

class TlsKeySecureTransport final : public TlsKeyGeneric
{
public:
    using TlsKeyGeneric::TlsKeyGeneric;

    QByteArray decrypt(Cipher cipher, const QByteArray &data,
                       const QByteArray &key, const QByteArray &iv) const override;
    QByteArray encrypt(Cipher cipher, const QByteArray &data,
                       const QByteArray &key, const QByteArray &iv) const override;

    Q_DISABLE_COPY_MOVE(TlsKeySecureTransport)
};

} // namespace QTlsPrivate

QT_END_NAMESPACE

#endif // QTLSKEY_ST_P_H
