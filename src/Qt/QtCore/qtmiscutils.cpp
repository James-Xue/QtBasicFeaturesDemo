#include "qtmiscutils.h"

namespace QtMiscUtils
{
    char toHexUpper(char32_t value) noexcept
    {
        return "0123456789ABCDEF"[value & 0xF];
    }

    char toHexLower(char32_t value) noexcept
    {
        return "0123456789abcdef"[value & 0xF];
    }

    [[nodiscard]] bool isHexDigit(char32_t c) noexcept
    {
        return (c >= '0' && c <= '9')
            || (c >= 'A' && c <= 'F')
            || (c >= 'a' && c <= 'f');
    }

    int fromHex(char32_t c) noexcept
    {
        return ((c >= '0') && (c <= '9')) ? int(c - '0') :
            ((c >= 'A') && (c <= 'F')) ? int(c - 'A' + 10) :
            ((c >= 'a') && (c <= 'f')) ? int(c - 'a' + 10) :
            /* otherwise */              -1;
    }

    char toOct(char32_t value) noexcept
    {
        return char('0' + (value & 0x7));
    }

    [[nodiscard]] bool isOctalDigit(char32_t c) noexcept
    {
        return c >= '0' && c <= '7';
    }

    int fromOct(char32_t c) noexcept
    {
        return isOctalDigit(c) ? int(c - '0') : -1;
    }

    [[nodiscard]] bool isAsciiDigit(char32_t c) noexcept
    {
        return c >= '0' && c <= '9';
    }

    bool isAsciiUpper(char32_t c) noexcept
    {
        return c >= 'A' && c <= 'Z';
    }

    bool isAsciiLower(char32_t c) noexcept
    {
        return c >= 'a' && c <= 'z';
    }

    bool isAsciiLetterOrNumber(char32_t c) noexcept
    {
        return  isAsciiDigit(c) || isAsciiLower(c) || isAsciiUpper(c);
    }

    char toAsciiLower(char ch) noexcept
    {
        return isAsciiUpper(ch) ? ch - 'A' + 'a' : ch;
    }

    char toAsciiUpper(char ch) noexcept
    {
        return isAsciiLower(ch) ? ch - 'a' + 'A' : ch;
    }

    int caseCompareAscii(char lhs, char rhs) noexcept
    {
        const char lhsLower = QtMiscUtils::toAsciiLower(lhs);
        const char rhsLower = QtMiscUtils::toAsciiLower(rhs);
        return int(uchar(lhsLower)) - int(uchar(rhsLower));
    }

    int isAsciiPrintable(char32_t ch) noexcept
    {
        return ch >= ' ' && ch < 0x7f;
    }

    int qt_lencmp(qsizetype lhs, qsizetype rhs) noexcept
    {
        return lhs == rhs ? 0 :
            lhs > rhs ? 1 :
            /* else */  -1;
    }
} // namespace QtMiscUtils
