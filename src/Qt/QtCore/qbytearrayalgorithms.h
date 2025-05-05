#ifndef QBYTEARRAYALGORITHMS_H
    #define QBYTEARRAYALGORITHMS_H

    #include <QtCore/qnamespace.h>
    #include <string.h>
    #include <stdarg.h>

    #if 0
        #pragma qt_class(QByteArrayAlgorithms)
    #endif

    QT_BEGIN_NAMESPACE

    /*****************************************************************************
      Safe and portable C string functions; extensions to standard string.h
     *****************************************************************************/

    [[nodiscard]] Q_DECL_PURE_FUNCTION Q_CORE_EXPORT
    const void *qmemrchr(const void *s, int needle, size_t n) noexcept;

    Q_CORE_EXPORT char *qstrdup(const char *);

    //inline size_t qstrlen(const char *str)
    //{
    //    QT_WARNING_PUSH

    //    #if defined(Q_CC_GNU_ONLY) && Q_CC_GNU >= 900 && Q_CC_GNU < 1000
    //        // spurious compiler warning (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91490#c6)
    //        // when Q_DECLARE_METATYPE_TEMPLATE_1ARG is used
    //        QT_WARNING_DISABLE_GCC("-Wstringop-overflow")
    //    #endif

    //    return str ? strlen(str) : 0;
    //    QT_WARNING_POP
    //}

    //inline size_t qstrnlen(const char *str, size_t maxlen)
    //{
    //    if (!str)
    //        return 0;
    //    auto end = static_cast<const char *>(memchr(str, '\0', maxlen));
    //    return end ? end - str : maxlen;
    //}

    // implemented in qbytearray.cpp
    Q_CORE_EXPORT char *qstrcpy(char *dst, const char *src);

    Q_CORE_EXPORT char *qstrncpy(char *dst, const char *src, size_t len);

    Q_CORE_EXPORT int qstrcmp(const char *str1, const char *str2);

    //inline int qstrncmp(const char *str1, const char *str2, size_t len)
    //{
    //    return (str1 && str2) ? strncmp(str1, str2, len)
    //        : (str1 ? 1 : (str2 ? -1 : 0));
    //}

    Q_CORE_EXPORT int qstricmp(const char *, const char *);

    Q_CORE_EXPORT int qstrnicmp(const char *, const char *, size_t len);

    Q_CORE_EXPORT int qstrnicmp(const char *, qsizetype, const char *, qsizetype = -1);

    #ifndef QT_NO_QSNPRINTF // use std::(v)snprintf() from <cstdio> instead
        // implemented in qvsnprintf.cpp
        Q_CORE_EXPORT int qvsnprintf(char *str, size_t n, const char *fmt, va_list ap)
            Q_ATTRIBUTE_FORMAT_PRINTF(3, 0);

        Q_CORE_EXPORT int qsnprintf(char *str, size_t n, const char *fmt, ...)
            Q_ATTRIBUTE_FORMAT_PRINTF(3, 4);
    #endif // QT_NO_QSNPRINTF

    QT_END_NAMESPACE
#endif // QBYTEARRAYALGORITHMS_H
