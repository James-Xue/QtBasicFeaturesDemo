#ifndef CSTRFUNS_H
    #define CSTRFUNS_H

    #include <qtypes.h>
    /*****************************************************************************
      Safe and portable C string functions;
      extensions to standard string.h
     *****************************************************************************/
    const void *qmemrchr(const void *s, int needle, size_t size) noexcept;

    char *qstrcpy(char *dst, const char *src);

    char *qstrncpy(char *dst, const char *src, size_t len);

    char *qstrdup(const char *src);

    int qstrcmp(const char *str1, const char *str2);

    int qstricmp(const char *str1, const char *str2);

    int qstrnicmp(const char *str1, const char *str2, size_t len);

    int qstrnicmp(const char *str1, qsizetype len1, const char *str2, qsizetype len2);

    size_t qstrlen(const char *str);

    size_t qstrnlen(const char *str, size_t maxlen);

    int qstrncmp(const char *str1, const char *str2, size_t len);

#endif // CSTRFUNS_H
