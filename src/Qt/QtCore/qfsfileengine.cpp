// Copyright (C) 2016 The Qt Company Ltd.
// Copyright (C) 2016 Intel Corporation.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <private/qfsfileengine_p.h>
#include <private/qfsfileengine_iterator_p.h>
#include <private/qfilesystemengine_p.h>
#include "qdatetime.h"
#include "qset.h"
#include <QtCore/qdebug.h>

#ifndef QT_NO_FSFILEENGINE

#include <errno.h>
#if defined(Q_OS_UNIX)
#include "private/qcore_unix_p.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#if defined(Q_OS_DARWIN)
# include <private/qcore_mac_p.h>
#endif

QT_BEGIN_NAMESPACE

using namespace Qt::StringLiterals;

#ifdef Q_OS_WIN
#  ifndef S_ISREG
#    define S_ISREG(x)   (((x) & S_IFMT) == S_IFREG)
#  endif
#  ifndef S_ISCHR
#    define S_ISCHR(x)   (((x) & S_IFMT) == S_IFCHR)
#  endif
#  ifndef S_ISFIFO
#    define S_ISFIFO(x) false
#  endif
#  ifndef S_ISSOCK
#    define S_ISSOCK(x) false
#  endif
#  ifndef INVALID_FILE_ATTRIBUTES
#    define INVALID_FILE_ATTRIBUTES (DWORD (-1))
#  endif
#endif

#ifdef Q_OS_WIN
// on Windows, read() and write() use int and unsigned int
typedef int SignedIOType;
typedef unsigned int UnsignedIOType;
#else
typedef ssize_t SignedIOType;
typedef size_t UnsignedIOType;
static_assert(sizeof(SignedIOType) == sizeof(UnsignedIOType),
                  "Unsupported: read/write return a type with different size as the len parameter");
#endif

/*! \class QFSFileEngine
    \inmodule QtCore
    \brief The QFSFileEngine class implements Qt's default file engine.
    \since 4.1
    \internal

    This class is part of the file engine framework in Qt. If you only want to
    access files or directories, use QFile, QFileInfo or QDir instead.

    QFSFileEngine is the default file engine for accessing regular files. It
    is provided for convenience; by subclassing this class, you can alter its
    behavior slightly, without having to write a complete QAbstractFileEngine
    subclass. To install your custom file engine, you must also subclass
    QAbstractFileEngineHandler and create an instance of your handler.

    It can also be useful to create a QFSFileEngine object directly if you
    need to use the local file system inside QAbstractFileEngine::create(), in
    order to avoid recursion (as higher-level classes tend to call
    QAbstractFileEngine::create()).
*/

//**************** QFSFileEnginePrivate
QFSFileEnginePrivate::QFSFileEnginePrivate() : QAbstractFileEnginePrivate()
{
    init();
}

/*!
    \internal
*/
void QFSFileEnginePrivate::init()
{
    is_sequential = 0;
    tried_stat = 0;
    need_lstat = 1;
    is_link = 0;
    openMode = QIODevice::NotOpen;
    fd = -1;
    fh = nullptr;
    lastIOCommand = IOFlushCommand;
    lastFlushFailed = false;
    closeFileHandle = false;
#ifdef Q_OS_WIN
    fileAttrib = INVALID_FILE_ATTRIBUTES;
    fileHandle = INVALID_HANDLE_VALUE;
    mapHandle = NULL;
    cachedFd = -1;
#endif
}

/*!
    Constructs a QFSFileEngine for the file name \a file.
*/
QFSFileEngine::QFSFileEngine(const QString &file)
    : QAbstractFileEngine(*new QFSFileEnginePrivate)
{
    Q_D(QFSFileEngine);
    d->fileEntry = QFileSystemEntry(file);
}

/*!
    Constructs a QFSFileEngine.
*/
QFSFileEngine::QFSFileEngine() : QAbstractFileEngine(*new QFSFileEnginePrivate)
{
}

/*!
    \internal
*/
QFSFileEngine::QFSFileEngine(QFSFileEnginePrivate &dd)
    : QAbstractFileEngine(dd)
{
}

/*!
    \internal
*/
ProcessOpenModeResult processOpenModeFlags(QIODevice::OpenMode openMode)
{
    ProcessOpenModeResult result;
    result.ok = false;
    if ((openMode & QFile::NewOnly) && (openMode & QFile::ExistingOnly)) {
        qWarning("NewOnly and ExistingOnly are mutually exclusive");
        result.error = "NewOnly and ExistingOnly are mutually exclusive"_L1;
        return result;
    }

    if ((openMode & QFile::ExistingOnly) && !(openMode & (QFile::ReadOnly | QFile::WriteOnly))) {
        qWarning("ExistingOnly must be specified alongside ReadOnly, WriteOnly, or ReadWrite");
        result.error =
                    "ExistingOnly must be specified alongside ReadOnly, WriteOnly, or ReadWrite"_L1;
        return result;
    }

    // Either Append or NewOnly implies WriteOnly
    if (openMode & (QFile::Append | QFile::NewOnly))
        openMode |= QFile::WriteOnly;

    // WriteOnly implies Truncate when ReadOnly, Append, and NewOnly are not set.
    if ((openMode & QFile::WriteOnly) && !(openMode & (QFile::ReadOnly | QFile::Append | QFile::NewOnly)))
        openMode |= QFile::Truncate;

    result.ok = true;
    result.openMode = openMode;
    return result;
}

/*!
    Destructs the QFSFileEngine.
*/
QFSFileEngine::~QFSFileEngine()
{
    Q_D(QFSFileEngine);
    if (d->closeFileHandle) {
        if (d->fh) {
            fclose(d->fh);
        } else if (d->fd != -1) {
            QT_CLOSE(d->fd);
        }
    }
    d->unmapAll();
}

/*!
    \reimp
*/
void QFSFileEngine::setFileName(const QString &file)
{
    Q_D(QFSFileEngine);
    d->init();
    d->fileEntry = QFileSystemEntry(file);
}

/*!
    \reimp
*/
bool QFSFileEngine::open(QIODevice::OpenMode openMode,
                         std::optional<QFile::Permissions> permissions)
{
    Q_ASSERT_X(openMode & QIODevice::Unbuffered, "QFSFileEngine::open",
               "QFSFileEngine no longer supports buffered mode; upper layer must buffer");

    Q_D(QFSFileEngine);
    if (d->fileEntry.isEmpty()) {
        qWarning("QFSFileEngine::open: No file name specified");
        setError(QFile::OpenError, "No file name specified"_L1);
        return false;
    }

    const ProcessOpenModeResult res = processOpenModeFlags(openMode);
    if (!res.ok) {
        setError(QFileDevice::OpenError, res.error);
        return false;
    }

    d->openMode = res.openMode;
    d->lastFlushFailed = false;
    d->tried_stat = 0;
    d->fh = nullptr;
    d->fd = -1;

    return d->nativeOpen(d->openMode, permissions);
}

/*!
    Opens the file handle \a fh in \a openMode mode. Returns \c true on
    success; otherwise returns \c false.
*/
bool QFSFileEngine::open(QIODevice::OpenMode openMode, FILE *fh)
{
    return open(openMode, fh, QFile::DontCloseHandle);
}

bool QFSFileEngine::open(QIODevice::OpenMode openMode, FILE *fh, QFile::FileHandleFlags handleFlags)
{
    Q_ASSERT_X(openMode & QIODevice::Unbuffered, "QFSFileEngine::open",
               "QFSFileEngine no longer supports buffered mode; upper layer must buffer");

    Q_D(QFSFileEngine);

    const ProcessOpenModeResult res = processOpenModeFlags(openMode);
    if (!res.ok) {
        setError(QFileDevice::OpenError, res.error);
        return false;
    }

    d->openMode = res.openMode;
    d->lastFlushFailed = false;
    d->closeFileHandle = handleFlags.testAnyFlag(QFile::AutoCloseHandle);
    d->fileEntry.clear();
    d->tried_stat = 0;
    d->fd = -1;

    return d->openFh(d->openMode, fh);
}

/*!
    Opens the file handle \a fh using the open mode \a flags.
*/
bool QFSFileEnginePrivate::openFh(QIODevice::OpenMode openMode, FILE *fh)
{
    Q_ASSERT_X(openMode & QIODevice::Unbuffered, "QFSFileEngine::open",
               "QFSFileEngine no longer supports buffered mode; upper layer must buffer");

    Q_Q(QFSFileEngine);
    this->fh = fh;
    fd = -1;

    // Seek to the end when in Append mode.
    if (openMode & QIODevice::Append) {
        int ret;
        do {
            ret = QT_FSEEK(fh, 0, SEEK_END);
        } while (ret != 0 && errno == EINTR);

        if (ret != 0) {
            q->setError(errno == EMFILE ? QFile::ResourceError : QFile::OpenError,
                        QSystemError::stdString(errno));

            this->openMode = QIODevice::NotOpen;
            this->fh = nullptr;

            return false;
        }
    }

    return true;
}

/*!
    Opens the file descriptor \a fd in \a openMode mode. Returns \c true
    on success; otherwise returns \c false.
*/
bool QFSFileEngine::open(QIODevice::OpenMode openMode, int fd)
{
    return open(openMode, fd, QFile::DontCloseHandle);
}

bool QFSFileEngine::open(QIODevice::OpenMode openMode, int fd, QFile::FileHandleFlags handleFlags)
{
    Q_D(QFSFileEngine);

    const ProcessOpenModeResult res = processOpenModeFlags(openMode);
    if (!res.ok) {
        setError(QFileDevice::OpenError, res.error);
        return false;
    }

    d->openMode = res.openMode;
    d->lastFlushFailed = false;
    d->closeFileHandle = handleFlags.testAnyFlag(QFile::AutoCloseHandle);
    d->fileEntry.clear();
    d->fh = nullptr;
    d->fd = -1;
    d->tried_stat = 0;

    return d->openFd(d->openMode, fd);
}


/*!
    Opens the file descriptor \a fd to the file engine, using the open mode \a
    flags.
*/
bool QFSFileEnginePrivate::openFd(QIODevice::OpenMode openMode, int fd)
{
    Q_Q(QFSFileEngine);
    this->fd = fd;
    fh = nullptr;

    // Seek to the end when in Append mode.
    if (openMode & QFile::Append) {
        QT_OFF_T ret;
        do {
            ret = QT_LSEEK(fd, 0, SEEK_END);
        } while (ret == -1 && errno == EINTR);

        if (ret == -1) {
            q->setError(errno == EMFILE ? QFile::ResourceError : QFile::OpenError,
                        QSystemError::stdString(errno));

            this->openMode = QIODevice::NotOpen;
            this->fd = -1;

            return false;
        }
    }

    return true;
}

/*!
    \reimp
*/
bool QFSFileEngine::close()
{
    Q_D(QFSFileEngine);
    d->openMode = QIODevice::NotOpen;
    return d->nativeClose();
}

/*!
    \internal
*/
bool QFSFileEnginePrivate::closeFdFh()
{
    Q_Q(QFSFileEngine);
    if (fd == -1 && !fh)
        return false;

    // Flush the file if it's buffered, and if the last flush didn't fail.
    bool flushed = !fh || (!lastFlushFailed && q->flush());
    bool closed = true;
    tried_stat = 0;

    // Close the file if we created the handle.
    if (closeFileHandle) {
        int ret;

        if (fh) {
            // Close buffered file.
            ret = fclose(fh);
        } else {
            // Close unbuffered file.
            ret = QT_CLOSE(fd);
        }

        // We must reset these guys regardless; calling close again after a
        // failed close causes crashes on some systems.
        fh = nullptr;
        fd = -1;
        closed = (ret == 0);
    }

    // Report errors.
    if (!flushed || !closed) {
        if (flushed) {
            // If not flushed, we want the flush error to fall through.
            q->setError(QFile::UnspecifiedError, QSystemError::stdString(errno));
        }
        return false;
    }

    return true;
}

/*!
    \reimp
*/
bool QFSFileEngine::flush()
{
    Q_D(QFSFileEngine);
    if ((d->openMode & QIODevice::WriteOnly) == 0) {
        // Nothing in the write buffers, so flush succeeds in doing
        // nothing.
        return true;
    }
    return d->nativeFlush();
}

/*!
    \reimp
*/
bool QFSFileEngine::syncToDisk()
{
    Q_D(QFSFileEngine);
    if ((d->openMode & QIODevice::WriteOnly) == 0)
        return true;
    return d->nativeSyncToDisk();
}

/*!
    \internal
*/
bool QFSFileEnginePrivate::flushFh()
{
    Q_Q(QFSFileEngine);

    // Never try to flush again if the last flush failed. Otherwise you can
    // get crashes on some systems (AIX).
    if (lastFlushFailed)
        return false;

    int ret = fflush(fh);

    lastFlushFailed = (ret != 0);
    lastIOCommand = QFSFileEnginePrivate::IOFlushCommand;

    if (ret != 0) {
        q->setError(errno == ENOSPC ? QFile::ResourceError : QFile::WriteError,
                    QSystemError::stdString(errno));
        return false;
    }
    return true;
}

/*!
    \reimp
*/
qint64 QFSFileEngine::size() const
{
    Q_D(const QFSFileEngine);
    return d->nativeSize();
}

/*!
    \internal
*/
void QFSFileEnginePrivate::unmapAll()
{
    if (!maps.isEmpty()) {
        const QList<uchar*> keys = maps.keys(); // Make a copy since unmap() modifies the map.
        for (int i = 0; i < keys.size(); ++i)
            unmap(keys.at(i));
    }
}

#ifndef Q_OS_WIN
/*!
    \internal
*/
qint64 QFSFileEnginePrivate::sizeFdFh() const
{
    Q_Q(const QFSFileEngine);
    const_cast<QFSFileEngine *>(q)->flush();

    tried_stat = 0;
    metaData.clearFlags(QFileSystemMetaData::SizeAttribute);
    if (!doStat(QFileSystemMetaData::SizeAttribute))
        return 0;
    return metaData.size();
}
#endif

/*!
    \reimp
*/
qint64 QFSFileEngine::pos() const
{
    Q_D(const QFSFileEngine);
    return d->nativePos();
}

/*!
    \internal
*/
qint64 QFSFileEnginePrivate::posFdFh() const
{
    if (fh)
        return qint64(QT_FTELL(fh));
    return QT_LSEEK(fd, 0, SEEK_CUR);
}

/*!
    \reimp
*/
bool QFSFileEngine::seek(qint64 pos)
{
    Q_D(QFSFileEngine);
    return d->nativeSeek(pos);
}

/*!
    \reimp
*/
QDateTime QFSFileEngine::fileTime(QFile::FileTime time) const
{
    Q_D(const QFSFileEngine);

    if (time == QFile::FileAccessTime) {
        // always refresh for the access time
        d->metaData.clearFlags(QFileSystemMetaData::AccessTime);
    }

    if (d->doStat(QFileSystemMetaData::Times))
        return d->metaData.fileTime(time);

    return QDateTime();
}


/*!
    \internal
*/
bool QFSFileEnginePrivate::seekFdFh(qint64 pos)
{
    Q_Q(QFSFileEngine);

    // On Windows' stdlib implementation, the results of calling fread and
    // fwrite are undefined if not called either in sequence, or if preceded
    // with a call to fflush().
    if (lastIOCommand != QFSFileEnginePrivate::IOFlushCommand && !q->flush())
        return false;

    if (pos < 0 || pos != qint64(QT_OFF_T(pos)))
        return false;

    if (fh) {
        // Buffered stdlib mode.
        int ret;
        do {
            ret = QT_FSEEK(fh, QT_OFF_T(pos), SEEK_SET);
        } while (ret != 0 && errno == EINTR);

        if (ret != 0) {
            q->setError(QFile::ReadError, QSystemError::stdString(errno));
            return false;
        }
    } else {
        // Unbuffered stdio mode.
        if (QT_LSEEK(fd, QT_OFF_T(pos), SEEK_SET) == -1) {
            q->setError(QFile::PositionError, QSystemError::stdString(errno));
            qWarning("QFile::at: Cannot set file position %lld", pos);
            return false;
        }
    }
    return true;
}

/*!
    \reimp
*/
int QFSFileEngine::handle() const
{
    Q_D(const QFSFileEngine);
    return d->nativeHandle();
}

/*!
    \reimp
*/
qint64 QFSFileEngine::read(char *data, qint64 maxlen)
{
    Q_D(QFSFileEngine);

    // On Windows' stdlib implementation, the results of calling fread and
    // fwrite are undefined if not called either in sequence, or if preceded
    // with a call to fflush().
    if (d->lastIOCommand != QFSFileEnginePrivate::IOReadCommand) {
        flush();
        d->lastIOCommand = QFSFileEnginePrivate::IOReadCommand;
    }

    return d->nativeRead(data, maxlen);
}

/*!
    \internal
*/
qint64 QFSFileEnginePrivate::readFdFh(char *data, qint64 len)
{
    Q_Q(QFSFileEngine);

    if (len < 0 || len != qint64(size_t(len))) {
        q->setError(QFile::ReadError, QSystemError::stdString(EINVAL));
        return -1;
    }

    qint64 readBytes = 0;
    bool eof = false;

    if (fh) {
        // Buffered stdlib mode.

        size_t result;
        do {
            result = fread(data + readBytes, 1, size_t(len - readBytes), fh);
            eof = feof(fh); // Doesn't change errno
            if (eof && result == 0) {
                // On OS X, this is needed, e.g., if a file was written to
                // through another stream since our last read. See test
                // tst_QFile::appendAndRead
                QT_FSEEK(fh, QT_FTELL(fh), SEEK_SET); // re-sync stream.
                break;
            }
            readBytes += result;
        } while (!eof && (result == 0 ? errno == EINTR : readBytes < len));

    } else if (fd != -1) {
        // Unbuffered stdio mode.

        SignedIOType result;
        do {
            // calculate the chunk size
            // on Windows or 32-bit no-largefile Unix, we'll need to read in chunks
            // we limit to the size of the signed type, otherwise we could get a negative number as a result
            quint64 wantedBytes = quint64(len) - quint64(readBytes);
            UnsignedIOType chunkSize = std::numeric_limits<SignedIOType>::max();
            if (chunkSize > wantedBytes)
                chunkSize = wantedBytes;
            result = QT_READ(fd, data + readBytes, chunkSize);
        } while (result > 0 && (readBytes += result) < len);

        // QT_READ (::read()) returns 0 to indicate end-of-file
        eof = result == 0;
    }

    if (!eof && readBytes == 0) {
        readBytes = -1;
        q->setError(QFile::ReadError, QSystemError::stdString(errno));
    }

    return readBytes;
}

/*!
    \reimp
*/
qint64 QFSFileEngine::readLine(char *data, qint64 maxlen)
{
    Q_D(QFSFileEngine);

    // On Windows' stdlib implementation, the results of calling fread and
    // fwrite are undefined if not called either in sequence, or if preceded
    // with a call to fflush().
    if (d->lastIOCommand != QFSFileEnginePrivate::IOReadCommand) {
        flush();
        d->lastIOCommand = QFSFileEnginePrivate::IOReadCommand;
    }

    return d->nativeReadLine(data, maxlen);
}

/*!
    \internal
*/
qint64 QFSFileEnginePrivate::readLineFdFh(char *data, qint64 maxlen)
{
    Q_Q(QFSFileEngine);
    if (!fh)
        return q->QAbstractFileEngine::readLine(data, maxlen);

    QT_OFF_T oldPos = 0;
#ifdef Q_OS_WIN
    bool seq = q->isSequential();
    if (!seq)
#endif
        oldPos = QT_FTELL(fh);

    // QIODevice::readLine() passes maxlen - 1 to QFile::readLineData()
    // because it has made space for the '\0' at the end of data.  But fgets
    // does the same, so we'd get two '\0' at the end - passing maxlen + 1
    // solves this.
    if (!fgets(data, int(maxlen + 1), fh)) {
        if (!feof(fh)) // Doesn't change errno
            q->setError(QFile::ReadError, QSystemError::stdString(errno));
        return -1;              // error
    }

#ifdef Q_OS_WIN
    if (seq)
        return qstrlen(data);
#endif

    qint64 lineLength = QT_FTELL(fh) - oldPos;
    return lineLength > 0 ? lineLength : qstrlen(data);
}

/*!
    \reimp
*/
qint64 QFSFileEngine::write(const char *data, qint64 len)
{
    Q_D(QFSFileEngine);
    d->metaData.clearFlags(QFileSystemMetaData::Times);

    // On Windows' stdlib implementation, the results of calling fread and
    // fwrite are undefined if not called either in sequence, or if preceded
    // with a call to fflush().
    if (d->lastIOCommand != QFSFileEnginePrivate::IOWriteCommand) {
        flush();
        d->lastIOCommand = QFSFileEnginePrivate::IOWriteCommand;
    }

    return d->nativeWrite(data, len);
}

/*!
    \internal
*/
qint64 QFSFileEnginePrivate::writeFdFh(const char *data, qint64 len)
{
    Q_Q(QFSFileEngine);

    if (len < 0 || len != qint64(size_t(len))) {
        q->setError(QFile::WriteError, QSystemError::stdString(EINVAL));
        return -1;
    }

    qint64 writtenBytes = 0;

    if (len) { // avoid passing nullptr to fwrite() or QT_WRITE() (UB)

        if (fh) {
            // Buffered stdlib mode.

            size_t result;
            do {
                result = fwrite(data + writtenBytes, 1, size_t(len - writtenBytes), fh);
                writtenBytes += result;
            } while (result == 0 ? errno == EINTR : writtenBytes < len);

        } else if (fd != -1) {
            // Unbuffered stdio mode.

            SignedIOType result;
            do {
                // calculate the chunk size
                // on Windows or 32-bit no-largefile Unix, we'll need to read in chunks
                // we limit to the size of the signed type, otherwise we could get a negative number as a result
                quint64 wantedBytes = quint64(len) - quint64(writtenBytes);
                UnsignedIOType chunkSize = std::numeric_limits<SignedIOType>::max();
                if (chunkSize > wantedBytes)
                    chunkSize = wantedBytes;
                result = QT_WRITE(fd, data + writtenBytes, chunkSize);
            } while (result > 0 && (writtenBytes += result) < len);
        }

    }

    if (len &&  writtenBytes == 0) {
        writtenBytes = -1;
        q->setError(errno == ENOSPC ? QFile::ResourceError : QFile::WriteError,
                    QSystemError::stdString(errno));
    } else {
        // reset the cached size, if any
        metaData.clearFlags(QFileSystemMetaData::SizeAttribute);
    }

    return writtenBytes;
}

#ifndef QT_NO_FILESYSTEMITERATOR
/*!
    \internal
*/
QAbstractFileEngine::IteratorUniquePtr
QFSFileEngine::beginEntryList(const QString &path, QDirListing::IteratorFlags filters,
                              const QStringList &filterNames)
{
    return std::make_unique<QFSFileEngineIterator>(path, filters, filterNames);
}
#endif // QT_NO_FILESYSTEMITERATOR

/*!
    \reimp
*/
bool QFSFileEngine::isSequential() const
{
    Q_D(const QFSFileEngine);
    if (d->is_sequential == 0)
        d->is_sequential = d->nativeIsSequential() ? 1 : 2;
    return d->is_sequential == 1;
}

/*!
    \internal
*/
#ifdef Q_OS_UNIX
bool QFSFileEnginePrivate::isSequentialFdFh() const
{
    if (doStat(QFileSystemMetaData::SequentialType))
        return metaData.isSequential();
    return true;
}
#endif

/*!
    \reimp
*/
bool QFSFileEngine::extension(Extension extension, const ExtensionOption *option, ExtensionReturn *output)
{
    Q_D(QFSFileEngine);
    if (extension == AtEndExtension && d->fh && isSequential())
        return feof(d->fh);

    if (extension == MapExtension) {
        const MapExtensionOption *options = (const MapExtensionOption*)(option);
        MapExtensionReturn *returnValue = static_cast<MapExtensionReturn*>(output);
        returnValue->address = d->map(options->offset, options->size, options->flags);
        return (returnValue->address != nullptr);
    }
    if (extension == UnMapExtension) {
        const UnMapExtensionOption *options = (const UnMapExtensionOption*)option;
        return d->unmap(options->address);
    }

    return false;
}

/*!
    \reimp
*/
bool QFSFileEngine::supportsExtension(Extension extension) const
{
    Q_D(const QFSFileEngine);
    if (extension == AtEndExtension && d->fh && isSequential())
        return true;
    if (extension == FastReadLineExtension && d->fh)
        return true;
    if (extension == FastReadLineExtension && d->fd != -1 && isSequential())
        return true;
    if (extension == UnMapExtension || extension == MapExtension)
        return true;
    return false;
}

/*! \fn QString QFSFileEngine::currentPath(const QString &fileName)
  For Unix, returns the current working directory for the file
  engine.

  For Windows, returns the canonicalized form of the current path used
  by the file engine for the drive specified by \a fileName.  On
  Windows, each drive has its own current directory, so a different
  path is returned for file names that include different drive names
  (e.g. A: or C:).

  \sa setCurrentPath()
*/

/*! \fn QFileInfoList QFSFileEngine::drives()
  For Windows, returns the list of drives in the file system as a list
  of QFileInfo objects. On Unix, only the root path is returned.
  On Windows, this function returns all drives (A:\, C:\, D:\, and so on).

  For Unix, the list contains just the root path "/".
*/

/*! \fn QString QFSFileEngine::fileName(QAbstractFileEngine::FileName file) const
  \reimp
*/

/*! \fn bool QFSFileEngine::setFileTime(const QDateTime &newDate, QFile::FileTime time)
  \reimp
*/

/*!
  Returns the home path of the current user.

  \sa rootPath()
*/
QString QFSFileEngine::homePath()
{
    return QFileSystemEngine::homePath();
}

/*!
  Returns the root path.

  \sa homePath()
*/
QString QFSFileEngine::rootPath()
{
    return QFileSystemEngine::rootPath();
}

/*!
  Returns the temporary path (i.e., a path in which it is safe
  to store temporary files).
*/
QString QFSFileEngine::tempPath()
{
    return QFileSystemEngine::tempPath();
}

/*! \fn bool QFSFileEngine::isRelativePath() const
  \reimp
*/

/*! \fn bool QFSFileEngine::link(const QString &newName)

  Creates a link from the file currently specified by fileName() to
  \a newName. What a link is depends on the underlying filesystem
  (be it a shortcut on Windows or a symbolic link on Unix). Returns
  \c true if successful; otherwise returns \c false.

  \note On Windows \a newName is expected to end with .lnk as the filename
  extension.
*/


/*! \fn uint QFSFileEngine::ownerId(QAbstractFileEngine::FileOwner own) const
  In Unix, if stat() is successful, the \c uid is returned if
  \a own is the owner. Otherwise the \c gid is returned. If stat()
  is unsuccessful, -2 is reuturned.

  For Windows, -2 is always returned.
*/

/*! \fn QString QFSFileEngine::owner(QAbstractFileEngine::FileOwner own) const
  \reimp
*/

/*!
  For Windows or Apple platforms, copy the file to file \a copyName.

  Not implemented for other Unix platforms.
*/
bool QFSFileEngine::copy(const QString &copyName)
{
    Q_D(QFSFileEngine);
    QSystemError error;
    bool ret = QFileSystemEngine::copyFile(d->fileEntry, QFileSystemEntry(copyName), error);
    if (!ret)
        setError(QFile::CopyError, error.toString());
    return ret;
}

/*!
  \reimp
*/
bool QFSFileEngine::remove()
{
    Q_D(QFSFileEngine);
    QSystemError error;
    bool ret = QFileSystemEngine::removeFile(d->fileEntry, error);
    d->metaData.clear();
    if (!ret)
        setError(QFile::RemoveError, error.toString());
    return ret;
}

/*
    An alternative to setFileName() when you have already constructed
    a QFileSystemEntry.
*/
void QFSFileEngine::setFileEntry(QFileSystemEntry &&entry)
{
    Q_D(QFSFileEngine);
    d->init();
    d->fileEntry = std::move(entry);
}

bool QFSFileEngine::rename_helper(const QString &newName, RenameMode mode)
{
    Q_D(QFSFileEngine);

    auto func = mode == Rename ? QFileSystemEngine::renameFile
                               : QFileSystemEngine::renameOverwriteFile;
    QSystemError error;
    auto newEntry = QFileSystemEntry(newName);
    const bool ret = func(d->fileEntry, newEntry, error);
    if (!ret) {
        setError(QFile::RenameError, error.toString());
        return false;
    }
    setFileEntry(std::move(newEntry));
    return true;
}

/*!
  \reimp
*/
bool QFSFileEngine::mkdir(const QString &name, bool createParentDirectories,
                          std::optional<QFile::Permissions> permissions) const
{
    return QFileSystemEngine::createDirectory(QFileSystemEntry(name), createParentDirectories,
                                              permissions);
}

/*!
  \reimp
*/
bool QFSFileEngine::rmdir(const QString &name, bool recurseParentDirectories) const
{
    return QFileSystemEngine::removeDirectory(QFileSystemEntry(name), recurseParentDirectories);
}


/*!
  Sets the current path (e.g., for QDir), to \a path. Returns \c true if the
  new path exists; otherwise this function does nothing, and returns \c false.

  \sa currentPath()
*/
bool QFSFileEngine::setCurrentPath(const QString &path)
{
    return QFileSystemEngine::setCurrentPath(QFileSystemEntry(path));
}

/*!
    Returns whether the file system considers the file name to be
    case sensitive.
*/
bool QFSFileEngine::caseSensitive() const
{
    Q_D(const QFSFileEngine);
    return QFileSystemEngine::isCaseSensitive(d->fileEntry, d->metaData);
}

/*! \fn bool QFSFileEngine::setPermissions(uint perms)
  \reimp
*/

/*! \fn bool QFSFileEngine::setSize(qint64 size)
  \reimp
*/

/*! \fn QAbstractFileEngine::FileFlags QFSFileEnginePrivate::getPermissions(QAbstractFileEngine::FileFlags type) const
    \internal
*/

QT_END_NAMESPACE

#endif // QT_NO_FSFILEENGINE
