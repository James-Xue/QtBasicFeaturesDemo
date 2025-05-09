// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QFILESYSTEMWATCHER_H
#define QFILESYSTEMWATCHER_H

#include <QtCore/qobject.h>

QT_REQUIRE_CONFIG(filesystemwatcher);

QT_BEGIN_NAMESPACE


class QFileSystemWatcherPrivate;

class Q_CORE_EXPORT QFileSystemWatcher : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QFileSystemWatcher)

public:
    QFileSystemWatcher(QObject *parent = nullptr);
    QFileSystemWatcher(const QStringList &paths, QObject *parent = nullptr);
    ~QFileSystemWatcher();

    bool addPath(const QString &file);
    QStringList addPaths(const QStringList &files);
    bool removePath(const QString &file);
    QStringList removePaths(const QStringList &files);

    QStringList files() const;
    QStringList directories() const;

Q_SIGNALS:
    void fileChanged(const QString &path, QPrivateSignal);
    void directoryChanged(const QString &path, QPrivateSignal);
};

QT_END_NAMESPACE

#endif // QFILESYSTEMWATCHER_H
