// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QANDROIDSYSTEMLOCALE_H
#define QANDROIDSYSTEMLOCALE_H

#include "private/qlocale_p.h"
#include <QtCore/qreadwritelock.h>

QT_BEGIN_NAMESPACE

class QAndroidSystemLocale : public QSystemLocale
{
    Q_DISABLE_COPY_MOVE(QAndroidSystemLocale)
public:
    QAndroidSystemLocale();

    QVariant query(QueryType type, QVariant &&in) const override;
    QLocale fallbackLocale() const override;

private:
    void getLocaleFromJava() const;

    QString convertTo24hFormat(const QString &format) const;
    QString timeToString(const QTime &time, QLocale::FormatType type) const;
    QString dateTimeToString(const QDateTime &dt, QLocale::FormatType type) const;

    mutable QLocale m_locale;
    mutable QReadWriteLock m_lock;
    mutable bool m_24hFormat = false;
};

QT_END_NAMESPACE

#endif // QANDROIDSYSTEMLOCALE_H
