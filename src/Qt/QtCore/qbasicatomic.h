#ifndef QBASICATOMIC_H
    #define QBASICATOMIC_H

    #include <QtCore/qatomic_cxx11.h>

    QT_WARNING_PUSH

    QT_WARNING_DISABLE_MSVC(4522)

    QT_BEGIN_NAMESPACE

    #if 0
        // silence syncqt warnings
        QT_END_NAMESPACE
        #pragma qt_no_master_include
        #pragma qt_sync_stop_processing
    #endif

    template <typename T>
    class QBasicAtomicInteger
    {
    public:
        typedef T Type;

        typedef QAtomicOps<T> Ops;

        // static check that this is a valid integer
        static_assert(std::is_integral_v<T>, "template parameter is not an integral type");
        static_assert(QAtomicOpsSupport<sizeof(T)>::IsSupported, "template parameter is an integral of a size not supported on this platform");

        typename Ops::Type _q_value;

        // Everything below is either implemented in ../arch/qatomic_XXX.h or (as
        // fallback) in qgenericatomic.h
        T loadRelaxed() const noexcept { return Ops::loadRelaxed(_q_value); }
        void storeRelaxed(T newValue) noexcept { Ops::storeRelaxed(_q_value, newValue); }

        T loadAcquire() const noexcept { return Ops::loadAcquire(_q_value); }
        void storeRelease(T newValue) noexcept { Ops::storeRelease(_q_value, newValue); }
        operator T() const noexcept { return loadAcquire(); }
        T operator=(T newValue) noexcept { storeRelease(newValue); return newValue; }

        static constexpr bool isReferenceCountingNative() noexcept { return Ops::isReferenceCountingNative(); }
        static constexpr bool isReferenceCountingWaitFree() noexcept { return Ops::isReferenceCountingWaitFree(); }

        bool ref() noexcept { return Ops::ref(_q_value); }
        bool deref() noexcept { return Ops::deref(_q_value); }

        static constexpr bool isTestAndSetNative() noexcept { return Ops::isTestAndSetNative(); }
        static constexpr bool isTestAndSetWaitFree() noexcept { return Ops::isTestAndSetWaitFree(); }

        bool testAndSetRelaxed(T expectedValue, T newValue) noexcept
        { return Ops::testAndSetRelaxed(_q_value, expectedValue, newValue); }
        bool testAndSetAcquire(T expectedValue, T newValue) noexcept
        { return Ops::testAndSetAcquire(_q_value, expectedValue, newValue); }
        bool testAndSetRelease(T expectedValue, T newValue) noexcept
        { return Ops::testAndSetRelease(_q_value, expectedValue, newValue); }
        bool testAndSetOrdered(T expectedValue, T newValue) noexcept
        { return Ops::testAndSetOrdered(_q_value, expectedValue, newValue); }

        bool testAndSetRelaxed(T expectedValue, T newValue, T &currentValue) noexcept
        { return Ops::testAndSetRelaxed(_q_value, expectedValue, newValue, &currentValue); }
        bool testAndSetAcquire(T expectedValue, T newValue, T &currentValue) noexcept
        { return Ops::testAndSetAcquire(_q_value, expectedValue, newValue, &currentValue); }
        bool testAndSetRelease(T expectedValue, T newValue, T &currentValue) noexcept
        { return Ops::testAndSetRelease(_q_value, expectedValue, newValue, &currentValue); }
        bool testAndSetOrdered(T expectedValue, T newValue, T &currentValue) noexcept
        { return Ops::testAndSetOrdered(_q_value, expectedValue, newValue, &currentValue); }

        static constexpr bool isFetchAndStoreNative() noexcept { return Ops::isFetchAndStoreNative(); }
        static constexpr bool isFetchAndStoreWaitFree() noexcept { return Ops::isFetchAndStoreWaitFree(); }

        T fetchAndStoreRelaxed(T newValue) noexcept
        { return Ops::fetchAndStoreRelaxed(_q_value, newValue); }
        T fetchAndStoreAcquire(T newValue) noexcept
        { return Ops::fetchAndStoreAcquire(_q_value, newValue); }
        T fetchAndStoreRelease(T newValue) noexcept
        { return Ops::fetchAndStoreRelease(_q_value, newValue); }
        T fetchAndStoreOrdered(T newValue) noexcept
        { return Ops::fetchAndStoreOrdered(_q_value, newValue); }

        static constexpr bool isFetchAndAddNative() noexcept { return Ops::isFetchAndAddNative(); }
        static constexpr bool isFetchAndAddWaitFree() noexcept { return Ops::isFetchAndAddWaitFree(); }

        T fetchAndAddRelaxed(T valueToAdd) noexcept
        { return Ops::fetchAndAddRelaxed(_q_value, valueToAdd); }
        T fetchAndAddAcquire(T valueToAdd) noexcept
        { return Ops::fetchAndAddAcquire(_q_value, valueToAdd); }
        T fetchAndAddRelease(T valueToAdd) noexcept
        { return Ops::fetchAndAddRelease(_q_value, valueToAdd); }
        T fetchAndAddOrdered(T valueToAdd) noexcept
        { return Ops::fetchAndAddOrdered(_q_value, valueToAdd); }

        T fetchAndSubRelaxed(T valueToAdd) noexcept
        { return Ops::fetchAndSubRelaxed(_q_value, valueToAdd); }
        T fetchAndSubAcquire(T valueToAdd) noexcept
        { return Ops::fetchAndSubAcquire(_q_value, valueToAdd); }
        T fetchAndSubRelease(T valueToAdd) noexcept
        { return Ops::fetchAndSubRelease(_q_value, valueToAdd); }
        T fetchAndSubOrdered(T valueToAdd) noexcept
        { return Ops::fetchAndSubOrdered(_q_value, valueToAdd); }

        T fetchAndAndRelaxed(T valueToAdd) noexcept
        { return Ops::fetchAndAndRelaxed(_q_value, valueToAdd); }
        T fetchAndAndAcquire(T valueToAdd) noexcept
        { return Ops::fetchAndAndAcquire(_q_value, valueToAdd); }
        T fetchAndAndRelease(T valueToAdd) noexcept
        { return Ops::fetchAndAndRelease(_q_value, valueToAdd); }
        T fetchAndAndOrdered(T valueToAdd) noexcept
        { return Ops::fetchAndAndOrdered(_q_value, valueToAdd); }

        T fetchAndOrRelaxed(T valueToAdd) noexcept
        { return Ops::fetchAndOrRelaxed(_q_value, valueToAdd); }
        T fetchAndOrAcquire(T valueToAdd) noexcept
        { return Ops::fetchAndOrAcquire(_q_value, valueToAdd); }
        T fetchAndOrRelease(T valueToAdd) noexcept
        { return Ops::fetchAndOrRelease(_q_value, valueToAdd); }
        T fetchAndOrOrdered(T valueToAdd) noexcept
        { return Ops::fetchAndOrOrdered(_q_value, valueToAdd); }

        T fetchAndXorRelaxed(T valueToAdd) noexcept
        { return Ops::fetchAndXorRelaxed(_q_value, valueToAdd); }
        T fetchAndXorAcquire(T valueToAdd) noexcept
        { return Ops::fetchAndXorAcquire(_q_value, valueToAdd); }
        T fetchAndXorRelease(T valueToAdd) noexcept
        { return Ops::fetchAndXorRelease(_q_value, valueToAdd); }
        T fetchAndXorOrdered(T valueToAdd) noexcept
        { return Ops::fetchAndXorOrdered(_q_value, valueToAdd); }

        T operator++() noexcept
        { return fetchAndAddOrdered(1) + 1; }
        T operator++(int) noexcept
        { return fetchAndAddOrdered(1); }
        T operator--() noexcept
        { return fetchAndSubOrdered(1) - 1; }
        T operator--(int) noexcept
        { return fetchAndSubOrdered(1); }

        T operator+=(T v) noexcept
        { return fetchAndAddOrdered(v) + v; }
        T operator-=(T v) noexcept
        { return fetchAndSubOrdered(v) - v; }
        T operator&=(T v) noexcept
        { return fetchAndAndOrdered(v) & v; }
        T operator|=(T v) noexcept
        { return fetchAndOrOrdered(v) | v; }
        T operator^=(T v) noexcept
        { return fetchAndXorOrdered(v) ^ v; }


        QBasicAtomicInteger() = default;
        constexpr QBasicAtomicInteger(T value) noexcept : _q_value(value) {}
        QBasicAtomicInteger(const QBasicAtomicInteger &) = delete;
        QBasicAtomicInteger &operator=(const QBasicAtomicInteger &) = delete;
        QBasicAtomicInteger &operator=(const QBasicAtomicInteger &) volatile = delete;
    };
    typedef QBasicAtomicInteger<int> QBasicAtomicInt;

    template <typename X>
    class QBasicAtomicPointer
    {
    public:
        typedef X *Type;
        typedef QAtomicOps<Type> Ops;
        typedef typename Ops::Type AtomicType;

        AtomicType _q_value;

        Type loadRelaxed() const noexcept { return Ops::loadRelaxed(_q_value); }
        void storeRelaxed(Type newValue) noexcept { Ops::storeRelaxed(_q_value, newValue); }

        operator Type() const noexcept { return loadAcquire(); }
        Type operator=(Type newValue) noexcept { storeRelease(newValue); return newValue; }

        // Atomic API, implemented in qatomic_XXX.h
        Type loadAcquire() const noexcept { return Ops::loadAcquire(_q_value); }
        void storeRelease(Type newValue) noexcept { Ops::storeRelease(_q_value, newValue); }

        static constexpr bool isTestAndSetNative() noexcept { return Ops::isTestAndSetNative(); }
        static constexpr bool isTestAndSetWaitFree() noexcept { return Ops::isTestAndSetWaitFree(); }

        bool testAndSetRelaxed(Type expectedValue, Type newValue) noexcept
        { return Ops::testAndSetRelaxed(_q_value, expectedValue, newValue); }
        bool testAndSetAcquire(Type expectedValue, Type newValue) noexcept
        { return Ops::testAndSetAcquire(_q_value, expectedValue, newValue); }
        bool testAndSetRelease(Type expectedValue, Type newValue) noexcept
        { return Ops::testAndSetRelease(_q_value, expectedValue, newValue); }
        bool testAndSetOrdered(Type expectedValue, Type newValue) noexcept
        { return Ops::testAndSetOrdered(_q_value, expectedValue, newValue); }

        bool testAndSetRelaxed(Type expectedValue, Type newValue, Type &currentValue) noexcept
        { return Ops::testAndSetRelaxed(_q_value, expectedValue, newValue, &currentValue); }
        bool testAndSetAcquire(Type expectedValue, Type newValue, Type &currentValue) noexcept
        { return Ops::testAndSetAcquire(_q_value, expectedValue, newValue, &currentValue); }
        bool testAndSetRelease(Type expectedValue, Type newValue, Type &currentValue) noexcept
        { return Ops::testAndSetRelease(_q_value, expectedValue, newValue, &currentValue); }
        bool testAndSetOrdered(Type expectedValue, Type newValue, Type &currentValue) noexcept
        { return Ops::testAndSetOrdered(_q_value, expectedValue, newValue, &currentValue); }

        static constexpr bool isFetchAndStoreNative() noexcept { return Ops::isFetchAndStoreNative(); }
        static constexpr bool isFetchAndStoreWaitFree() noexcept { return Ops::isFetchAndStoreWaitFree(); }

        Type fetchAndStoreRelaxed(Type newValue) noexcept
        { return Ops::fetchAndStoreRelaxed(_q_value, newValue); }
        Type fetchAndStoreAcquire(Type newValue) noexcept
        { return Ops::fetchAndStoreAcquire(_q_value, newValue); }
        Type fetchAndStoreRelease(Type newValue) noexcept
        { return Ops::fetchAndStoreRelease(_q_value, newValue); }
        Type fetchAndStoreOrdered(Type newValue) noexcept
        { return Ops::fetchAndStoreOrdered(_q_value, newValue); }

        static constexpr bool isFetchAndAddNative() noexcept { return Ops::isFetchAndAddNative(); }
        static constexpr bool isFetchAndAddWaitFree() noexcept { return Ops::isFetchAndAddWaitFree(); }

        Type fetchAndAddRelaxed(qptrdiff valueToAdd) noexcept
        { return Ops::fetchAndAddRelaxed(_q_value, valueToAdd); }
        Type fetchAndAddAcquire(qptrdiff valueToAdd) noexcept
        { return Ops::fetchAndAddAcquire(_q_value, valueToAdd); }
        Type fetchAndAddRelease(qptrdiff valueToAdd) noexcept
        { return Ops::fetchAndAddRelease(_q_value, valueToAdd); }
        Type fetchAndAddOrdered(qptrdiff valueToAdd) noexcept
        { return Ops::fetchAndAddOrdered(_q_value, valueToAdd); }

        Type fetchAndSubRelaxed(qptrdiff valueToAdd) noexcept
        { return Ops::fetchAndSubRelaxed(_q_value, valueToAdd); }
        Type fetchAndSubAcquire(qptrdiff valueToAdd) noexcept
        { return Ops::fetchAndSubAcquire(_q_value, valueToAdd); }
        Type fetchAndSubRelease(qptrdiff valueToAdd) noexcept
        { return Ops::fetchAndSubRelease(_q_value, valueToAdd); }
        Type fetchAndSubOrdered(qptrdiff valueToAdd) noexcept
        { return Ops::fetchAndSubOrdered(_q_value, valueToAdd); }

        Type operator++() noexcept
        { return fetchAndAddOrdered(1) + 1; }
        Type operator++(int) noexcept
        { return fetchAndAddOrdered(1); }
        Type operator--() noexcept
        { return fetchAndSubOrdered(1) - 1; }
        Type operator--(int) noexcept
        { return fetchAndSubOrdered(1); }
        Type operator+=(qptrdiff valueToAdd) noexcept
        { return fetchAndAddOrdered(valueToAdd) + valueToAdd; }
        Type operator-=(qptrdiff valueToSub) noexcept
        { return fetchAndSubOrdered(valueToSub) - valueToSub; }

        QBasicAtomicPointer() = default;
        constexpr QBasicAtomicPointer(Type value) noexcept : _q_value(value) {}
        QBasicAtomicPointer(const QBasicAtomicPointer &) = delete;
        QBasicAtomicPointer &operator=(const QBasicAtomicPointer &) = delete;
        QBasicAtomicPointer &operator=(const QBasicAtomicPointer &) volatile = delete;
    };

    #ifndef Q_BASIC_ATOMIC_INITIALIZER
        #define Q_BASIC_ATOMIC_INITIALIZER(a) { (a) }
    #endif

    QT_END_NAMESPACE

    QT_WARNING_POP
#endif // QBASICATOMIC_H
