#ifndef QTPRIVATE_H
    #define QTPRIVATE_H

    // STL
    #include <type_traits>

    //Qt
    #include <QtCore/qbytearrayview.h>
 
    // Forward declare
    //class QByteArrayView;

    namespace QtPrivate
    {
        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        bool startsWith(QByteArrayView haystack, QByteArrayView needle) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        bool endsWith(QByteArrayView haystack, QByteArrayView needle) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        qsizetype findByteArray(QByteArrayView haystack, qsizetype from, char needle) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        qsizetype findByteArray(QByteArrayView haystack, qsizetype from, QByteArrayView needle) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        qsizetype lastIndexOf(QByteArrayView haystack, qsizetype from, uchar needle) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        qsizetype lastIndexOf(QByteArrayView haystack, qsizetype from, QByteArrayView needle) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        qsizetype count(QByteArrayView haystack, QByteArrayView needle) noexcept;

        [[nodiscard]] Q_CORE_EXPORT
        int compareMemory(QByteArrayView lhs, QByteArrayView rhs);

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        QByteArrayView trimmed(QByteArrayView view) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        bool isValidUtf8(QByteArrayView view) noexcept;

        template <typename T>
        class ParsedNumber
        {
            T m_value;
            quint32 m_error : 1;
            quint32 m_reserved : 31;
            void *m_reserved2 = nullptr;

        public:
            constexpr ParsedNumber() noexcept
                : m_value()
                , m_error(true)
                , m_reserved(0)
            {
            }

            constexpr explicit ParsedNumber(T v)
                : m_value(v)
                , m_error(false)
                , m_reserved(0)
            {
            }

            // minimal optional-like API:
            explicit operator bool() const noexcept { return !m_error; }

            T &operator*() { Q_ASSERT(*this); return m_value; }

            const T &operator*() const { Q_ASSERT(*this); return m_value; }

            T *operator->() noexcept { return *this ? &m_value : nullptr; }

            const T *operator->() const noexcept { return *this ? &m_value : nullptr; }

            template <typename U> // not = T, as that'd allow calls that are incompatible with std::optional
            T value_or(U &&u) const { return *this ? m_value : T(std::forward<U>(u)); }
        };

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        ParsedNumber<double> toDouble(QByteArrayView view) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        ParsedNumber<float> toFloat(QByteArrayView view) noexcept;

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        ParsedNumber<qlonglong> toSignedInteger(QByteArrayView view, int base);

        [[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION
        ParsedNumber<qulonglong> toUnsignedInteger(QByteArrayView view, int base);

        // QByteArrayView has incomplete type here, and we can't include qbytearrayview.h,
        // since it includes qbytearrayalgorithms.h. Use the ByteArrayView template type as
        // a workaround.
        template <typename T,
                  typename ByteArrayView,
                  typename = std::enable_if_t<std::is_same_v<ByteArrayView, QByteArrayView>>>
        static inline T toIntegral(ByteArrayView data, bool *ok, int base)
        {
            const auto val = [&]
                {
                    if constexpr (std::is_unsigned_v<T>)
                        return toUnsignedInteger(data, base);
                    else
                        return toSignedInteger(data, base);
                }();

            const bool failed = !val || T(*val) != *val;
            if (ok)
            {
                *ok = !failed;
            }

            if (failed)
            {
                return 0;
            }

            return T(*val);
        }
    } // namespace QtPrivate

#endif // QTPRIVATE_H
