// STL
#include <string.h>

// Qt
#include <qtmiscutils.h>
#include <qminmax.h>

// Myself
#include "cstrfuns.h"

/*****************************************************************************
    Safe and portable C string functions;
    extensions to standard string.h
*****************************************************************************/
const void *qmemrchr(const void *s, int needle, size_t size) noexcept
{
    //#if QT_CONFIG(memrchr)
    //    return memrchr(s, needle, size);
    //#endif

    const uchar *b = static_cast<const uchar *>(s);
    const uchar *n = b + size;

    while (n-- != b)
    {
        if (*n == uchar(needle))
        {
            return n;
        }
    }

    return nullptr;
}

char *qstrcpy(char *dst, const char *src)
{
    if (nullptr == src)
    {
        return nullptr;
    }

#ifdef Q_CC_MSVC
    const size_t len = strlen(src);
    // This is actually not secure!!! It will be fixed
    // properly in a later release!
    if (len >= 0 && strcpy_s(dst, len + 1, src) == 0)
        return dst;
    return nullptr;
#else
    return strcpy(dst, src);
#endif
}

char *qstrncpy(char *dst, const char *src, size_t len)
{
    if ((nullptr != dst) &&
        (len > 0))
    {
        *dst = '\0';
        if (nullptr != src)
        {
#ifdef Q_CC_MSVC
            strncat_s(dst, len - 1, src,  1024);
#else
            /*std::*/strncat(dst, src, len - 1);
#endif
        }
    }
    return src ? dst : nullptr;
}

char *qstrdup(const char *src)
{
    if (nullptr == src)
    {
        return nullptr;
    }

    char *dst = new char[strlen(src) + 1];
    return qstrcpy(dst, src);
}

int qstrcmp(const char *str1, const char *str2)
{
    return (str1 && str2) ? strcmp(str1, str2)
        : (str1 ? 1 : (str2 ? -1 : 0));
}

int qstricmp(const char *str1, const char *str2)
{
    const uchar *s1 = reinterpret_cast<const uchar *>(str1);
    const uchar *s2 = reinterpret_cast<const uchar *>(str2);
    if (!s1)
        return s2 ? -1 : 0;
    if (!s2)
        return 1;

    enum { Incomplete = 256 };
    qptrdiff offset = 0;
    auto innerCompare = [=, &offset](qptrdiff max, bool unlimited) {
        max += offset;
        do {
            uchar c = s1[offset];
            if (int res = QtMiscUtils::caseCompareAscii(c, s2[offset]))
                return res;
            if (!c)
                return 0;
            ++offset;
        } while (unlimited || offset < max);
        return int(Incomplete);
        };

#if defined(__SSE4_1__) && !(defined(__SANITIZE_ADDRESS__) || __has_feature(address_sanitizer))
    enum { PageSize = 4096, PageMask = PageSize - 1 };
    const __m128i zero = _mm_setzero_si128();
    forever{
        // Calculate how many bytes we can load until we cross a page boundary
        // for either source. This isn't an exact calculation, just something
        // very quick.
        quintptr u1 = quintptr(s1 + offset);
        quintptr u2 = quintptr(s2 + offset);
        size_t n = PageSize - ((u1 | u2) & PageMask);

        qptrdiff maxoffset = offset + n;
        for (; offset + 16 <= maxoffset; offset += sizeof(__m128i)) {
            // load 16 bytes from either source
            __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(s1 + offset));
            __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(s2 + offset));

            // compare the two against each other
            __m128i cmp = _mm_cmpeq_epi8(a, b);

            // find NUL terminators too
            cmp = _mm_min_epu8(cmp, a);
            cmp = _mm_cmpeq_epi8(cmp, zero);

            // was there any difference or a NUL?
            uint mask = _mm_movemask_epi8(cmp);
            if (mask) {
                // yes, find out where
                uint start = qCountTrailingZeroBits(mask);
                uint end = sizeof(mask) * 8 - qCountLeadingZeroBits(mask);
                Q_ASSERT(end >= start);
                offset += start;
                n = end - start;
                break;
            }
        }

        // using SIMD could cause a page fault, so iterate byte by byte
        int res = innerCompare(n, false);
        if (res != Incomplete)
            return res;
    }
#endif

    return innerCompare(-1, true);
}

int qstrnicmp(const char *str1, const char *str2, size_t len)
{
    const uchar *s1 = reinterpret_cast<const uchar *>(str1);
    const uchar *s2 = reinterpret_cast<const uchar *>(str2);
    if (!s1 || !s2)
        return s1 ? 1 : (s2 ? -1 : 0);
    for (; len--; ++s1, ++s2) {
        const uchar c = *s1;
        if (int res = QtMiscUtils::caseCompareAscii(c, *s2))
            return res;
        if (!c)                                // strings are equal
            break;
    }
    return 0;
}

int qstrnicmp(const char *str1, qsizetype len1, const char *str2, qsizetype len2)
{
    Q_ASSERT(len1 >= 0);
    Q_ASSERT(len2 >= -1);
    const uchar *s1 = reinterpret_cast<const uchar *>(str1);
    const uchar *s2 = reinterpret_cast<const uchar *>(str2);
    if (!s1 || !len1) {
        if (len2 == 0)
            return 0;
        if (len2 == -1)
            return (!s2 || !*s2) ? 0 : -1;
        Q_ASSERT(s2);
        return -1;
    }
    if (!s2)
        return len1 == 0 ? 0 : 1;

    if (len2 == -1) {
        // null-terminated str2
        qsizetype i;
        for (i = 0; i < len1; ++i)
        {
            const uchar c = s2[i];
            if (!c)
                return 1;

            if (int res = QtMiscUtils::caseCompareAscii(s1[i], c))
                return res;
        }
        return s2[i] ? -1 : 0;
    }
    else
    {
        // not null-terminated
        const qsizetype len = qMin(len1, len2);
        for (qsizetype i = 0; i < len; ++i)
        {
            if (int res = QtMiscUtils::caseCompareAscii(s1[i], s2[i]))
                return res;
        }
        if (len1 == len2)
            return 0;
        return len1 < len2 ? -1 : 1;
    }
}

size_t qstrlen(const char *str)
{
    QT_WARNING_PUSH

    #if defined(Q_CC_GNU_ONLY) && Q_CC_GNU >= 900 && Q_CC_GNU < 1000
        // spurious compiler warning (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91490#c6)
        // when Q_DECLARE_METATYPE_TEMPLATE_1ARG is used
        QT_WARNING_DISABLE_GCC("-Wstringop-overflow")
    #endif

    return str ? strlen(str) : 0;
    QT_WARNING_POP
}

size_t qstrnlen(const char *str, size_t maxlen)
{
    if (nullptr == str)
    {
        return 0;
    }

    auto end = static_cast<const char *>(memchr(str, '\0', maxlen));
    return end ? end - str : maxlen;
}

int qstrncmp(const char *str1, const char *str2, size_t len)
{
    return (str1 && str2) ? strncmp(str1, str2, len)
        : (str1 ? 1 : (str2 ? -1 : 0));
}


/*****************************************************************************
  // API note: this function can't process a number with more than 2.1 billion digits
*****************************************************************************/
template <typename Char>
static Q_ALWAYS_INLINE void qulltoString_helper(qulonglong number, int base, Char *&p)
{
    // Performance-optimized code. Compiler can generate faster code when base is known.
    switch (base) {
#define BIG_BASE_LOOP(b)                                  \
    do {                                                  \
        const int r = number % b;                         \
        *--p = Char((r < 10 ? '0' : 'a' - 10) + r); \
        number /= b;                                      \
    } while (number)
#ifndef __OPTIMIZE_SIZE__
#    define SMALL_BASE_LOOP(b)             \
        do {                               \
            *--p = Char('0' + number % b); \
            number /= b;                   \
        } while (number)

    case 2: SMALL_BASE_LOOP(2); break;
    case 8: SMALL_BASE_LOOP(8); break;
    case 10: SMALL_BASE_LOOP(10); break;
    case 16: BIG_BASE_LOOP(16); break;
#undef SMALL_BASE_LOOP
#endif
    default: BIG_BASE_LOOP(base); break;
#undef BIG_BASE_LOOP
    }
}

char *qulltoa2(char *p, qulonglong n, int base)
{
#if defined(QT_CHECK_RANGE)
    if (base < 2 || base > 36) {
        qWarning("QByteArray::setNum: Invalid base %d", base);
        base = 10;
    }
#endif
    qulltoString_helper(n, base, p);
    return p;
}
