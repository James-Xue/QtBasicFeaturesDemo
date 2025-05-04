#ifndef QTMISCUTILS_H
    #define QTMISCUTILS_H

    #include <qtypes.h>

    namespace QtMiscUtils
    {
        char toHexUpper(char32_t value) noexcept;

        char toHexLower(char32_t value) noexcept;

        [[nodiscard]] bool isHexDigit(char32_t c) noexcept;

        int fromHex(char32_t c) noexcept;

        char toOct(char32_t value) noexcept;

        [[nodiscard]] bool isOctalDigit(char32_t c) noexcept;

        int fromOct(char32_t c) noexcept;

        [[nodiscard]] bool isAsciiDigit(char32_t c) noexcept;

        bool isAsciiUpper(char32_t c) noexcept;

        bool isAsciiLower(char32_t c) noexcept;

        bool isAsciiLetterOrNumber(char32_t c) noexcept;

        char toAsciiLower(char ch) noexcept;

        char toAsciiUpper(char ch) noexcept;

        int caseCompareAscii(char lhs, char rhs) noexcept;

        int isAsciiPrintable(char32_t ch) noexcept;

        int qt_lencmp(qsizetype lhs, qsizetype rhs) noexcept;
    } // namespace QtMiscUtils

#endif // QTMISCUTILS_H
