// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QTEST_NETWORK_H
#define QTEST_NETWORK_H

#include <QtTest/qtesttostring.h>

// enable NETWORK features
#ifndef QT_NETWORK_LIB
#define QT_NETWORK_LIB
#endif

#if 0
#pragma qt_class(QtTestNetwork)
#endif

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkCookie>
#include <QtNetwork/QNetworkReply>

#if 0
// inform syncqt
#pragma qt_no_master_include
#endif

QT_BEGIN_NAMESPACE

namespace QTest
{
template<>
inline char *toString<QHostAddress>(const QHostAddress &addr)
{
    switch (addr.protocol()) {
    case QAbstractSocket::UnknownNetworkLayerProtocol:
        return qstrdup("<unknown address (parse error)>");
    case QAbstractSocket::AnyIPProtocol:
        return qstrdup("QHostAddress::Any");
    case QAbstractSocket::IPv4Protocol:
    case QAbstractSocket::IPv6Protocol:
        break;
    }

    return toString(addr.toString());
}
} // namespace QTest

inline char *toString(QNetworkReply::NetworkError code)
{
    const QMetaObject *mo = &QNetworkReply::staticMetaObject;
    int index = mo->indexOfEnumerator("NetworkError");
    if (index == -1)
        return qstrdup("");

    QMetaEnum qme = mo->enumerator(index);
    return qstrdup(qme.valueToKey(code));
}

inline char *toString(const QNetworkCookie &cookie)
{
    return QTest::toString(cookie.toRawForm());
}

inline char *toString(const QList<QNetworkCookie> &list)
{
    QByteArray result = "QList(";
    if (!list.isEmpty()) {
        for (const QNetworkCookie &cookie : list)
            result += "QNetworkCookie(" + cookie.toRawForm() + "), ";
        result.chop(2); // remove trailing ", "
    }
    result.append(')');
    return QTest::toString(result);
}

QT_END_NAMESPACE

#endif
