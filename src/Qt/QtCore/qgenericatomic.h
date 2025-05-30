



#ifndef QGENERICATOMIC_H
    #define QGENERICATOMIC_H

    #include <QtCore/qcompilerdetection.h>
    #include <QtCore/qtconfigmacros.h>
    #include <QtCore/qtypes.h>

    QT_BEGIN_NAMESPACE

    #if 0
        // silence syncqt warnings
        QT_END_NAMESPACE
        #pragma qt_sync_skip_header_check
        #pragma qt_sync_stop_processing
    #endif

    template<int Size> struct QAtomicOpsSupport
    {
        enum { IsSupported = (Size == sizeof(int) || Size == sizeof(qptrdiff)) };
    };

    template <typename T> struct QAtomicAdditiveType
    {
        typedef T AdditiveT;
        static const int AddScale = 1;
    };

    template <typename T> struct QAtomicAdditiveType<T *>
    {
        typedef qptrdiff AdditiveT;
        static const int AddScale = sizeof(T);
    };

    QT_END_NAMESPACE
#endif // QGENERICATOMIC_H
