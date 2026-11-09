#ifndef CPU_BENCHMARK_H
#define CPU_BENCHMARK_H

#include <cstdint>

class CpuBenchmark
{
public:

    // Constructor
    CpuBenchmark();

    // Get available logical CPU threads
    unsigned int getCpuThreads() const;

    // Run benchmark for a specific thread count
    void runBenchmark(unsigned int threadCount,
                      uint64_t totalIterations);

private:

    // CPU workload function
    static uint64_t calculate(uint64_t start,
                              uint64_t iterations);

};

#endif