#ifndef QUNICODETABLES_H
    #define QUNICODETABLES_H

    #include <QtCore/qcompilerdetection.h>
    #include <QtCore/private/qunicodetables_p.h>

    QT_BEGIN_NAMESPACE

    namespace QUnicodeTables
    {
        constexpr unsigned int MaxSpecialCaseLength = 3;
        extern unsigned short specialCaseMap[];
        extern unsigned short uc_decomposition_trie[];
        extern unsigned short uc_decomposition_map[];

        Q_DECL_CONST_FUNCTION
        /*static*/ /*inline*/ const Properties *qGetProp(char32_t ucs4) noexcept;

        Q_DECL_CONST_FUNCTION
        /*static*/ /*inline*/ const Properties *qGetProp(char16_t ucs2) noexcept;

#define GET_DECOMPOSITION_INDEX(ucs4) \
           (ucs4 < 0x3400 \
            ? (QUnicodeTables::uc_decomposition_trie[QUnicodeTables::uc_decomposition_trie[ucs4 >> 4] + (ucs4 & 0xf)]) \
            : ucs4 < 0x30000 \
            ? QUnicodeTables::uc_decomposition_trie[QUnicodeTables::uc_decomposition_trie[((ucs4 - 0x3400) >> 8) + 0x340] + (ucs4 & 0xff)] \
            : 0xffff)

        extern unsigned short uc_ligature_trie[];
        extern unsigned short uc_ligature_map[];

#define GET_LIGATURE_INDEX(ucs4) \
           (ucs4 < 0x3100 \
            ? (QUnicodeTables::uc_ligature_trie[QUnicodeTables::uc_ligature_trie[ucs4 >> 5] + (ucs4 & 0x1f)]) \
            : ucs4 < 0x12000 \
            ? QUnicodeTables::uc_ligature_trie[QUnicodeTables::uc_ligature_trie[((ucs4 - 0x3100) >> 8) + 0x188] + (ucs4 & 0xff)] \
            : 0xffff)
    } // namespace QUnicodeTables

    QT_END_NAMESPACE
#endif // QUNICODETABLES_H
