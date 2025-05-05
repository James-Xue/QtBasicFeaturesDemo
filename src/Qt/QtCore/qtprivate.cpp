#include "qtprivate.h"
//#include <QtCore/qtmiscutils.h>
#include <QtCore/cstrfuns.h>

static qsizetype qFindByteArray(const char *haystack0, qsizetype l, qsizetype from, const char *needle,
    qsizetype sl)
{
    /*
        We use some hashing for efficiency's sake. Instead of
        comparing strings, we compare the hash value of str with that
        of a part of this QByteArray. Only if that matches, we call memcmp().
    */
    const char *haystack = haystack0 + from;
    const char *end = haystack0 + (l - sl);
    const qregisteruint sl_minus_1 = sl - 1;
    qregisteruint hashNeedle = 0, hashHaystack = 0;
    qsizetype idx;
    for (idx = 0; idx < sl; ++idx)
    {
        hashNeedle = ((hashNeedle << 1) + needle[idx]);
        hashHaystack = ((hashHaystack << 1) + haystack[idx]);
    }
    hashHaystack -= *(haystack + sl_minus_1);

    while (haystack <= end)
    {
        hashHaystack += *(haystack + sl_minus_1);
        if ((hashHaystack == hashNeedle) &&
            (*needle == *haystack) &&
            (memcmp(needle, haystack, sl) == 0))
        {
            return haystack - haystack0;
        }

        if (sl_minus_1 < sizeof(sl_minus_1) * CHAR_BIT)
        {
            hashHaystack -= qregisteruint(*haystack) << sl_minus_1;
        }

        hashHaystack <<= 1;
        ++haystack;
    }
    return -1;
}

static inline void bm_init_skiptable(const uchar *cc, qsizetype len, uchar *skiptable)
{
    int l = int(qMin(len, qsizetype(255)));
    memset(skiptable, l, 256 * sizeof(uchar));
    cc += len - l;
    while (l--)
    {
        skiptable[*cc++] = l;
    }
}

static inline qsizetype bm_find(const uchar *cc, qsizetype l, qsizetype index, const uchar *puc,
    qsizetype pl, const uchar *skiptable)
{
    if (pl == 0)
    {
        return index > l ? -1 : index;
    }

    const qsizetype pl_minus_one = pl - 1;
    const uchar *current = cc + index + pl_minus_one;
    const uchar *end = cc + l;
    while (current < end)
    {
        qsizetype skip = skiptable[*current];
        if (!skip)
        {
            // possible match
            while (skip < pl)
            {
                if (*(current - skip) != puc[pl_minus_one - skip])
                {
                    break;
                }

                skip++;
            }
            if (skip > pl_minus_one) // we have a match
            {
                return (current - cc) - skip + 1;
            }

            // in case we don't have a match we are a bit inefficient as we only skip by one
            // when we have the non matching char in the string.
            if (skiptable[*(current - skip)] == pl)
            {
                skip = pl - skip;
            }
            else
            {
                skip = 1;
            }
        }

        if (current > end - skip)
        {
            break;
        }
        current += skip;
    }
    return -1; // not found
}

Q_NEVER_INLINE
static qsizetype qFindByteArrayBoyerMoore(const char *haystack, qsizetype haystackLen, qsizetype haystackOffset,
    const char *needle, qsizetype needleLen)
{
    uchar skiptable[256];
    bm_init_skiptable((const uchar *)needle, needleLen, skiptable);
    if (haystackOffset < 0)
    {
        haystackOffset = 0;
    }

    return bm_find((const uchar *)haystack, haystackLen, haystackOffset, (const uchar *)needle, needleLen,
        skiptable);
}

static qsizetype lastIndexOfHelper(const char *haystack, qsizetype l, const char *needle, qsizetype ol,
    qsizetype from)
{
    auto delta = l - ol;
    if (from < 0)
    {
        from = delta;
    }

    if (from < 0 || from > l)
    {
        return -1;
    }

    if (from > delta)
    {
        from = delta;
    }

    const char *end = haystack;
    haystack += from;
    const qregisteruint ol_minus_1 = ol - 1;
    const char *n = needle + ol_minus_1;
    const char *h = haystack + ol_minus_1;
    qregisteruint hashNeedle = 0, hashHaystack = 0;
    qsizetype idx;

    for (idx = 0; idx < ol; ++idx)
    {
        hashNeedle = ((hashNeedle << 1) + *(n - idx));
        hashHaystack = ((hashHaystack << 1) + *(h - idx));
    }

    hashHaystack -= *haystack;
    while (haystack >= end)
    {
        hashHaystack += *haystack;
        if (hashHaystack == hashNeedle && memcmp(needle, haystack, ol) == 0)
        {
            return haystack - end;
        }

        --haystack;
        if (ol_minus_1 < sizeof(ol_minus_1) * CHAR_BIT)
        {
            hashHaystack -= qregisteruint(*(haystack + ol)) << ol_minus_1;
        }

        hashHaystack <<= 1;
    }
    return -1;
}

static qsizetype countCharHelper(QByteArrayView haystack, char needle) noexcept
{
    qsizetype num = 0;
    for (char ch : haystack)
    {
        if (ch == needle)
        {
            ++num;
        }
    }
    return num;
}

namespace QtPrivate
{
    bool startsWith(QByteArrayView haystack, QByteArrayView needle) noexcept
    {
        if (haystack.size() < needle.size())
        {
            return false;
        }

        if (haystack.data() == needle.data() || needle.size() == 0)
        {
            return true;
        }

        return memcmp(haystack.data(), needle.data(), needle.size()) == 0;
    }

    bool endsWith(QByteArrayView haystack, QByteArrayView needle) noexcept
    {
        if (haystack.size() < needle.size())
        {
            return false;
        }

        if (haystack.end() == needle.end() || needle.size() == 0)
        {
            return true;
        }

        return memcmp(haystack.end() - needle.size(), needle.data(), needle.size()) == 0;
    }

    qsizetype findByteArray(QByteArrayView haystack, qsizetype from, char needle) noexcept
    {
        if (from < 0)
        {
            from = qMax(from + haystack.size(), qsizetype(0));
        }

        if (from < haystack.size())
        {
            const char *const b = haystack.data();
            if (const auto n = static_cast<const char *>(
                memchr(b + from, needle, static_cast<size_t>(haystack.size() - from))))
            {
                return n - b;
            }
        }
        return -1;
    }

    qsizetype findByteArray(QByteArrayView haystack, qsizetype from, QByteArrayView needle) noexcept
    {
        const auto haystack0 = haystack.data();
        const auto l = haystack.size();
        const auto sl = needle.size();
//#if !QT_CONFIG(memmem)
//        if (sl == 1)
//            return findByteArray(haystack, from, needle.front());
//#endif

        if (from < 0)
        {
            from += l;
        }

        if (std::size_t(sl + from) > std::size_t(l))
        {
            return -1;
        }

        if (!sl)
        {
            return from;
        }

        if (!l)
        {
            return -1;
        }

//#if QT_CONFIG(memmem)
//        auto where = memmem(haystack0 + from, l - from, needle.data(), sl);
//        return where ? static_cast<const char *>(where) - haystack0 : -1;
//#endif

        /*
          We use the Boyer-Moore algorithm in cases where the overhead
          for the skip table should pay off, otherwise we use a simple
          hash function.
        */
        if (l > 500 && sl > 5)
        {
            return qFindByteArrayBoyerMoore(haystack0, l, from, needle.data(), sl);
        }
        return qFindByteArray(haystack0, l, from, needle.data(), sl);
    }

    qsizetype lastIndexOf(QByteArrayView haystack, qsizetype from, uchar needle) noexcept
    {
        if (from < 0)
        {
            from = qMax(from + haystack.size(), qsizetype(0));
        }
        else
        {
            from = qMin(from, haystack.size() - 1);
        }

        const char *const b = haystack.data();
        const void *n = b ? qmemrchr(b, needle, from + 1) : nullptr;
        return n ? static_cast<const char *>(n) - b : -1;
    }

    qsizetype lastIndexOf(QByteArrayView haystack, qsizetype from, QByteArrayView needle) noexcept
    {
        if (haystack.isEmpty())
        {
            if (needle.isEmpty() && from == 0)
            {
                return 0;
            }
            return -1;
        }
        const auto ol = needle.size();
        if (1 == ol)
        {
            return QtPrivate::lastIndexOf(haystack, from, needle.front());
        }
        return lastIndexOfHelper(haystack.data(), haystack.size(), needle.data(), ol, from);
    }

    qsizetype count(QByteArrayView haystack, QByteArrayView needle) noexcept
    {
        if (needle.size() == 0)
        {
            return haystack.size() + 1;
        }

        if (needle.size() == 1)
        {
            return countCharHelper(haystack, needle[0]);
        }

        qsizetype num = 0;
        qsizetype i = -1;
        if (haystack.size() > 500 && needle.size() > 5)
        {
            //QByteArrayMatcher matcher(needle);
            //while ((i = matcher.indexIn(haystack, i + 1)) != -1)
            {
                ++num;
            }
        }
        else
        {
            while ((i = haystack.indexOf(needle, i + 1)) != -1)
            {
                ++num;
            }
        }
        return num;
    }

    int compareMemory(QByteArrayView lhs, QByteArrayView rhs)
    {
        if (!lhs.isNull() && !rhs.isNull())
        {
            int ret = memcmp(lhs.data(), rhs.data(), qMin(lhs.size(), rhs.size()));
            if (ret != 0)
            {
                return ret;
            }
        }

        // they matched qMin(l1, l2) bytes
        // so the longer one is lexically after the shorter one
        return lhs.size() == rhs.size() ? 0 : lhs.size() > rhs.size() ? 1 : -1;
    }

    QByteArrayView trimmed(QByteArrayView /*view*/) noexcept
    {
        //const auto [start, stop] = QStringAlgorithms<QByteArrayView>::trimmed_helper_positions(view);
        //return QByteArrayView(start, stop);
        return QByteArrayView();
    }

    bool isValidUtf8(QByteArrayView /*view*/) noexcept
    {
        //return QUtf8::isValidUtf8(s).isValidUtf8;
        return false;
    }

    ParsedNumber<double> toDouble(QByteArrayView /*view*/) noexcept
    {
        //auto r = qt_asciiToDouble(view.data(), view.size(), WhitespacesAllowed);
        //if (r.ok())
        //{
        //    return ParsedNumber{ r.result };
        //}
        //else
        {
            return {};
        }
    }

    ParsedNumber<float> QtPrivate::toFloat(QByteArrayView /*view*/) noexcept
    {
        //if (const auto r = toDouble(view))
        //{
        //    bool ok = true;
        //    const auto f = QLocaleData::convertDoubleToFloat(*r, &ok);
        //    if (ok)
        //    {
        //        return ParsedNumber(f);
        //    }
        //}
        return {};
    }

    ParsedNumber<qlonglong> QtPrivate::toSignedInteger(QByteArrayView view, int /*base*/)
    {
    #if defined(QT_CHECK_RANGE)
        if (base != 0 && (base < 2 || base > 36))
        {
            qWarning("QByteArray::toIntegral: Invalid base %d", base);
            base = 10;
        }
    #endif
        if (view.isEmpty())
        {
            return {};
        }
    
        //const QSimpleParsedNumber r = QLocaleData::bytearrayToLongLong(view, base);
        //if (r.ok())
        //{
        //    return ParsedNumber(r.result);
        //}
        return {};
    }

    ParsedNumber<qulonglong> QtPrivate::toUnsignedInteger(QByteArrayView view, int /*base*/)
    {
    #if defined(QT_CHECK_RANGE)
        if (base != 0 && (base < 2 || base > 36))
        {
            qWarning("QByteArray::toIntegral: Invalid base %d", base);
            base = 10;
        }
    #endif
        if (view.isEmpty())
        {
            return {};
        }
    
        //const QSimpleParsedNumber r = QLocaleData::bytearrayToUnsLongLong(view, base);
        //if (r.ok())
        //{
        //    return ParsedNumber(r.result);
        //}
        return {};
    }

} // namespace QtPrivate
