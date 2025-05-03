// Copyright (C) 2016 The Qt Company Ltd.



#ifndef QBENCHMARKMETRIC_H
#define QBENCHMARKMETRIC_H

#include <QtTest/qttestglobal.h>

QT_BEGIN_NAMESPACE


namespace QTest {

enum QBenchmarkMetric {
    FramesPerSecond,
    BitsPerSecond,
    BytesPerSecond,
    WalltimeMilliseconds,
    CPUTicks,
    InstructionReads,
    Events,
    WalltimeNanoseconds,
    BytesAllocated,
    CPUMigrations,
    CPUCycles,
    BusCycles,
    StalledCycles,
    Instructions,
    BranchInstructions,
    BranchMisses,
    CacheReferences,
    CacheReads,
    CacheWrites,
    CachePrefetches,
    CacheMisses,
    CacheReadMisses,
    CacheWriteMisses,
    CachePrefetchMisses,
    ContextSwitches,
    PageFaults,
    MinorPageFaults,
    MajorPageFaults,
    AlignmentFaults,
    EmulationFaults,
    RefCPUCycles,
};

}

QT_END_NAMESPACE

#endif // QBENCHMARK_H
