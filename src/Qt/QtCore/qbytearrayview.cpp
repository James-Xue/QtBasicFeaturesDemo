#include "qbytearrayview.h"

QT_BEGIN_NAMESPACE

constexpr qsizetype QByteArrayView::lengthHelperCharArray(const char *data, size_t size) noexcept
{
    const auto it = std::char_traits<char>::find(data, size, '\0');
    const auto end = it ? it : std::next(data, size);
    return qsizetype(std::distance(data, end));
}

constexpr const QByteArrayView::storage_type *QByteArrayView::castHelper(const storage_type *data) noexcept
{
    return data;
}

constexpr QByteArrayView::QByteArrayView() noexcept
    : m_size(0)
    , m_data(nullptr)
{
}

constexpr QByteArrayView::QByteArrayView(std::nullptr_t) noexcept
    : QByteArrayView()
{
}

[[nodiscard]] constexpr qsizetype QByteArrayView::size() const noexcept
{
    return m_size;
}

[[nodiscard]] constexpr QByteArrayView::const_pointer QByteArrayView::data() const noexcept
{
    return m_data;
}

[[nodiscard]] constexpr QByteArrayView::const_pointer QByteArrayView::constData() const noexcept
{
    return data();
}

[[nodiscard]] constexpr char QByteArrayView::operator[] (qsizetype n) const
{
    verify(n, 1);
    return m_data[n];
}

// QByteArray API
[[nodiscard]] constexpr char QByteArrayView::at(qsizetype n) const
{
    return (*this)[n];
}

[[nodiscard]] constexpr QByteArrayView QByteArrayView::first(qsizetype n) const
{
    verify(0, n);
    return sliced(0, n);
}

[[nodiscard]] constexpr QByteArrayView QByteArrayView::last(qsizetype n) const
{
    verify(0, n);
    return sliced(size() - n, n);
}

[[nodiscard]] constexpr QByteArrayView QByteArrayView::sliced(qsizetype pos) const
{
    verify(pos, 0);
    return QByteArrayView(data() + pos, size() - pos);
}

[[nodiscard]] constexpr QByteArrayView QByteArrayView::sliced(qsizetype pos, qsizetype n) const
{
    verify(pos, n);
    return QByteArrayView(data() + pos, n);
}

constexpr QByteArrayView &QByteArrayView::slice(qsizetype pos)
{
    *this = sliced(pos); return *this;
}

constexpr QByteArrayView &QByteArrayView::slice(qsizetype pos, qsizetype n)
{
    *this = sliced(pos, n); return *this;
}

[[nodiscard]] constexpr QByteArrayView QByteArrayView::chopped(qsizetype len) const
{
    verify(0, len);
    return sliced(0, size() - len);
}

[[nodiscard]] constexpr QByteArrayView QByteArrayView::left(qsizetype n) const
{
    if (n < 0 || n > size()) n = size();
    return QByteArrayView(data(), n);
}

[[nodiscard]] constexpr QByteArrayView QByteArrayView::right(qsizetype n) const
{
    if (n < 0 || n > size()) n = size();
    if (n < 0) n = 0;
    return QByteArrayView(data() + size() - n, n);
}

[[nodiscard]] constexpr QByteArrayView QByteArrayView::mid(qsizetype pos, qsizetype n/* = -1*/) const
{
    using namespace QtPrivate;
    auto result = QContainerImplHelper::mid(size(), &pos, &n);
    return result == QContainerImplHelper::Null ? QByteArrayView()
        : QByteArrayView(m_data + pos, n);
}

constexpr void QByteArrayView::truncate(qsizetype n)
{
    verify(0, n); m_size = n;
}
constexpr void QByteArrayView::chop(qsizetype n)
{
    verify(0, n); m_size -= n;
}

// Defined in qbytearray.cpp:
[[nodiscard]] QByteArrayView QByteArrayView::trimmed() const noexcept
{
    return QtPrivate::trimmed(*this);
}

[[nodiscard]] short QByteArrayView::toShort(bool *ok/* = nullptr*/, int base/* = 10*/) const
{
    return QtPrivate::toIntegral<short>(*this, ok, base);
}

[[nodiscard]] ushort QByteArrayView::toUShort(bool *ok/* = nullptr*/, int base/* = 10*/) const
{
    return QtPrivate::toIntegral<ushort>(*this, ok, base);
}

[[nodiscard]] int QByteArrayView::toInt(bool *ok/* = nullptr*/, int base/* = 10*/) const
{
    return QtPrivate::toIntegral<int>(*this, ok, base);
}

[[nodiscard]] uint QByteArrayView::toUInt(bool *ok/* = nullptr*/, int base/* = 10*/) const
{
    return QtPrivate::toIntegral<uint>(*this, ok, base);
}

[[nodiscard]] long QByteArrayView::toLong(bool *ok/* = nullptr*/, int base/* = 10*/) const
{
    return QtPrivate::toIntegral<long>(*this, ok, base);
}

[[nodiscard]] ulong QByteArrayView::toULong(bool *ok/* = nullptr*/, int base/* = 10*/) const
{
    return QtPrivate::toIntegral<ulong>(*this, ok, base);
}

[[nodiscard]] qlonglong QByteArrayView::toLongLong(bool *ok/* = nullptr*/, int base/* = 10*/) const
{
    return QtPrivate::toIntegral<qlonglong>(*this, ok, base);
}

[[nodiscard]] qulonglong QByteArrayView::toULongLong(bool *ok/* = nullptr*/, int base/* = 10*/) const
{
    return QtPrivate::toIntegral<qulonglong>(*this, ok, base);
}

[[nodiscard]] float QByteArrayView::toFloat(bool *ok/* = nullptr*/) const
{
    const auto r = QtPrivate::toFloat(*this);
    if (ok)
        *ok = bool(r);
    return r.value_or(0.0f);
}

[[nodiscard]] double QByteArrayView::toDouble(bool *ok/* = nullptr*/) const
{
    const auto r = QtPrivate::toDouble(*this);
    if (ok)
        *ok = bool(r);
    return r.value_or(0.0);
}

[[nodiscard]] bool QByteArrayView::startsWith(QByteArrayView other) const noexcept
{
    return QtPrivate::startsWith(*this, other);
}

[[nodiscard]] constexpr bool QByteArrayView::startsWith(char c) const noexcept
{
    return !empty() && front() == c;
}

[[nodiscard]] bool QByteArrayView::endsWith(QByteArrayView other) const noexcept
{
    return QtPrivate::endsWith(*this, other);
}

[[nodiscard]] constexpr bool QByteArrayView::endsWith(char c) const noexcept
{
    return !empty() && back() == c;
}

[[nodiscard]] qsizetype QByteArrayView::indexOf(QByteArrayView a, qsizetype from/* = 0*/) const noexcept
{
    return QtPrivate::findByteArray(*this, from, a);
}

[[nodiscard]] qsizetype QByteArrayView::indexOf(char ch, qsizetype from/* = 0*/) const noexcept
{
    return QtPrivate::findByteArray(*this, from, ch);
}

[[nodiscard]] bool QByteArrayView::contains(QByteArrayView a) const noexcept
{
    return indexOf(a) != qsizetype(-1);
}

[[nodiscard]] bool QByteArrayView::contains(char c) const noexcept
{
    return indexOf(c) != qsizetype(-1);
}

[[nodiscard]] qsizetype QByteArrayView::lastIndexOf(QByteArrayView a) const noexcept
{
    return lastIndexOf(a, size());
}

[[nodiscard]] qsizetype QByteArrayView::lastIndexOf(QByteArrayView a, qsizetype from) const noexcept
{
    return QtPrivate::lastIndexOf(*this, from, a);
}

[[nodiscard]] qsizetype QByteArrayView::lastIndexOf(char ch, qsizetype from/* = -1*/) const noexcept
{
    return QtPrivate::lastIndexOf(*this, from, ch);
}

[[nodiscard]] qsizetype QByteArrayView::count(QByteArrayView a) const noexcept
{
    return QtPrivate::count(*this, a);
}

[[nodiscard]] qsizetype QByteArrayView::count(char ch) const noexcept
{
    return QtPrivate::count(*this, QByteArrayView(&ch, 1));
}

[[nodiscard]] inline bool QByteArrayView::isValidUtf8() const noexcept
{
    return QtPrivate::isValidUtf8(*this);
}

// STL compatibility API:
[[nodiscard]] constexpr QByteArrayView::const_iterator QByteArrayView::begin()   const noexcept
{
    return data();
}

[[nodiscard]] constexpr QByteArrayView::const_iterator QByteArrayView::end()     const noexcept
{
    return data() + size();
}

[[nodiscard]] constexpr QByteArrayView::const_iterator QByteArrayView::cbegin()  const noexcept
{
    return begin();
}

[[nodiscard]] constexpr QByteArrayView::const_iterator QByteArrayView::cend()    const noexcept
{
    return end();
}

[[nodiscard]] constexpr QByteArrayView::const_reverse_iterator QByteArrayView::rbegin()  const noexcept
{
    return const_reverse_iterator(end());
}

[[nodiscard]] constexpr QByteArrayView::const_reverse_iterator QByteArrayView::rend()    const noexcept
{
    return const_reverse_iterator(begin());
}

[[nodiscard]] constexpr QByteArrayView::const_reverse_iterator QByteArrayView::crbegin() const noexcept
{
    return rbegin();
}

[[nodiscard]] constexpr QByteArrayView::const_reverse_iterator QByteArrayView::crend()   const noexcept
{
    return rend();
}

[[nodiscard]] constexpr bool QByteArrayView::empty() const noexcept
{
    return size() == 0;
}

[[nodiscard]] constexpr char QByteArrayView::front() const
{
    Q_ASSERT(!empty()); return m_data[0];
}

[[nodiscard]] constexpr char QByteArrayView::back()  const
{
    Q_ASSERT(!empty()); return m_data[m_size - 1];
}

[[nodiscard]] constexpr Q_IMPLICIT QByteArrayView::operator std::string_view() const noexcept
{
    return std::string_view(m_data, size_t(m_size));
}

[[nodiscard]] constexpr qsizetype QByteArrayView::max_size() const noexcept { return maxSize(); }

// Qt compatibility API:
[[nodiscard]] constexpr bool QByteArrayView::isNull() const noexcept
{
    return !m_data;
}

[[nodiscard]] constexpr bool QByteArrayView::isEmpty() const noexcept
{
    return empty();
}

[[nodiscard]] constexpr qsizetype QByteArrayView::length() const noexcept
{
    return size();
}

[[nodiscard]] constexpr char QByteArrayView::first() const
{
    return front();
}

[[nodiscard]] constexpr char QByteArrayView::last()  const
{
    return back();
}

[[nodiscard]] constexpr qsizetype QByteArrayView::maxSize() noexcept
{
    // -1 to deal with the pointer one-past-the-end;
    return QtPrivate::MaxAllocSize - 1;
}

Q_ALWAYS_INLINE constexpr void QByteArrayView::verify([[maybe_unused]] qsizetype pos/* = 0*/,
    [[maybe_unused]] qsizetype n/* = 1*/) const
{
    Q_ASSERT(pos >= 0);
    Q_ASSERT(pos <= size());
    Q_ASSERT(n >= 0);
    Q_ASSERT(n <= size() - pos);
}

int QByteArrayView::compare(QByteArrayView a, Qt::CaseSensitivity cs) const noexcept
{
    return cs == Qt::CaseSensitive ? QtPrivate::compareMemory(*this, a) :
        qstrnicmp(data(), size(), a.data(), a.size());
}

QT_END_NAMESPACE
