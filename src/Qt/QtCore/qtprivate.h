#ifndef QTPRIVATE_H
    #define QTPRIVATE_H

    #include <type_traits>

    // Forward declare
    class QByteArrayView;

    namespace QtPrivate
    {
        // QByteArrayView has incomplete type here, and we can't include qbytearrayview.h,
        // since it includes qbytearrayalgorithms.h. Use the ByteArrayView template type as
        // a workaround.
        template <typename T, typename ByteArrayView,
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

        //[[nodiscard]] Q_CORE_EXPORT Q_DECL_PURE_FUNCTION bool isValidUtf8(QByteArrayView s) noexcept;
    } // namespace QtPrivate

#endif // QTPRIVATE_H
