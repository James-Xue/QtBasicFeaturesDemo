// Copyright (C) 2012 David Faure <faure@kde.org>


#ifndef QSAVEFILE_H
#define QSAVEFILE_H

#include <QtCore/qglobal.h>

#if QT_CONFIG(temporaryfile)

#include <QtCore/qfiledevice.h>
#include <QtCore/qstring.h>

#ifdef open
#error qsavefile.h must be included before any header file that defines open
#endif

QT_BEGIN_NAMESPACE

class QAbstractFileEngine;
class QSaveFilePrivate;

class Q_CORE_EXPORT QSaveFile : public QFileDevice
{
#ifndef QT_NO_QOBJECT
    Q_OBJECT
#endif
    Q_DECLARE_PRIVATE(QSaveFile)

public:

    explicit QSaveFile(const QString &name);
#ifndef QT_NO_QOBJECT
    explicit QSaveFile(QObject *parent = nullptr);
    explicit QSaveFile(const QString &name, QObject *parent);
#endif
    ~QSaveFile();

    QString fileName() const override;
    void setFileName(const QString &name);

    QFILE_MAYBE_NODISCARD bool open(OpenMode flags) override;
    bool commit();

    void cancelWriting();

    void setDirectWriteFallback(bool enabled);
    bool directWriteFallback() const;

protected:
    qint64 writeData(const char *data, qint64 len) override;

private:
    void close() override;
#if !QT_CONFIG(translation)
    static QString tr(const char *string) { return QString::fromLatin1(string); }
#endif

private:
    Q_DISABLE_COPY(QSaveFile)
};

QT_END_NAMESPACE

#endif // QT_CONFIG(temporaryfile)

#endif // QSAVEFILE_H
