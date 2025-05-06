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

int qstrncmp(const char *str1, const char *str2, size_t len)
{
    return (str1 && str2) ? strncmp(str1, str2, len)
        : (str1 ? 1 : (str2 ? -1 : 0));
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

qsizetype qustrlen(const char16_t *str) noexcept
{
    //#if defined(__SSE2__) && !(defined(__SANITIZE_ADDRESS__) || __has_feature(address_sanitizer)) && !(defined(__SANITIZE_THREAD__) || __has_feature(thread_sanitizer))
    //        return qustrlen_sse2(str);
    //#endif

    if constexpr (sizeof(wchar_t) == sizeof(char16_t))
    {
        return wcslen(reinterpret_cast<const wchar_t *>(str));
    }
    else
    {
        qsizetype result = 0;
        while (*str++)
        {
            ++result;
        }
        return result;
    }
}

qsizetype qustrnlen(const char16_t */*str*/, qsizetype /*maxlen*/) noexcept
{
    //return qustrchr({ str, maxlen }, u'\0') - str;
    return 1024;
}

/*!
 * \internal
 *
 * Searches for character \a c in the string \a str and returns a pointer to
 * it. Unlike strchr() and wcschr() (but like glibc's strchrnul()), if the
 * character is not found, this function returns a pointer to the end of the
 * string -- that is, \c{str.end()}.
 */
 //Q_NEVER_INLINE
 //const char16_t *QtPrivate::qustrchr(QStringView str, char16_t c) noexcept
 //{
 //    const char16_t *n = str.utf16();
 //    const char16_t *e = n + str.size();
 //
 //#ifdef __SSE2__
 //    bool loops = true;
 //    // Using the PMOVMSKB instruction, we get two bits for each character
 //    // we compare.
 //    __m128i mch;
 //    if constexpr (UseAvx2) {
 //        // we're going to read n[0..15] (32 bytes)
 //        __m256i mch256 = _mm256_set1_epi32(c | (c << 16));
 //        for (const char16_t *next = n + 16; next <= e; n = next, next += 16) {
 //            __m256i data = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(n));
 //            __m256i result = _mm256_cmpeq_epi16(data, mch256);
 //            uint mask = uint(_mm256_movemask_epi8(result));
 //            if (mask) {
 //                uint idx = qCountTrailingZeroBits(mask);
 //                return n + idx / 2;
 //            }
 //        }
 //        loops = false;
 //        mch = _mm256_castsi256_si128(mch256);
 //    } else {
 //        mch = _mm_set1_epi32(c | (c << 16));
 //    }
 //
 //    auto hasMatch = [mch, &n](__m128i data, ushort validityMask) {
 //        __m128i result = _mm_cmpeq_epi16(data, mch);
 //        uint mask = uint(_mm_movemask_epi8(result));
 //        if ((mask & validityMask) == 0)
 //            return false;
 //        uint idx = qCountTrailingZeroBits(mask);
 //        n += idx / 2;
 //        return true;
 //    };
 //
 //    // we're going to read n[0..7] (16 bytes)
 //    for (const char16_t *next = n + 8; next <= e; n = next, next += 8) {
 //        __m128i data = _mm_loadu_si128(reinterpret_cast<const __m128i *>(n));
 //        if (hasMatch(data, 0xffff))
 //            return n;
 //
 //        if (!loops) {
 //            n += 8;
 //            break;
 //        }
 //    }
 //
 //#if !defined(__OPTIMIZE_SIZE__)
 //    // we're going to read n[0..3] (8 bytes)
 //    if (e - n > 3) {
 //        __m128i data = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(n));
 //        if (hasMatch(data, 0xff))
 //            return n;
 //
 //        n += 4;
 //    }
 //
 //    return UnrollTailLoop<3>::exec(e - n, e,
 //                                   [=](qsizetype i) { return n[i] == c; },
 //                                   [=](qsizetype i) { return n + i; });
 //#endif
 //#elif defined(__ARM_NEON__)
 //    const uint16x8_t vmask = qvsetq_n_u16(1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7);
 //    const uint16x8_t ch_vec = vdupq_n_u16(c);
 //    for (const char16_t *next = n + 8; next <= e; n = next, next += 8) {
 //        uint16x8_t data = vld1q_u16(reinterpret_cast<const uint16_t *>(n));
 //        uint mask = vaddvq_u16(vandq_u16(vceqq_u16(data, ch_vec), vmask));
 //        if (ushort(mask)) {
 //            // found a match
 //            return n + qCountTrailingZeroBits(mask);
 //        }
 //    }
 //#endif // aarch64
 //
 //    return std::find(n, e, c);
 //}

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
