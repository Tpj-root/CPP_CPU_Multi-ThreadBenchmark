#include <iostream>
#include <thread>
#include <cstdint>

#include "CpuBenchmark.h"


int main()
{
    CpuBenchmark cpu;

    // Detect CPU threads
    unsigned int maxThreads = cpu.getCpuThreads();

    if (maxThreads == 0)
    {
        std::cout << "Unable to detect CPU threads\n";
        return 1;
    }


    std::cout << "\n====================================\n";
    std::cout << "       PURE C++ CPU BENCHMARK\n";
    std::cout << "====================================\n\n";


    std::cout << "Available logical threads: "
              << maxThreads << '\n';


    // Total CPU workload
    uint64_t iterations = 50000000ULL;


    std::cout << "\nTotal iterations: "
              << iterations << '\n';


    std::cout << "\n";
    std::cout << "Threads     Time (sec)      Speed (iter/sec)     Checksum\n";

    std::cout << "-------------------------------------------------------------\n";


    // Test from 1 thread to maximum logical threads
    for (unsigned int i = 1; i <= maxThreads; ++i)
    {
        cpu.runBenchmark(i, iterations);
    }


    std::cout << "\n====================================\n";
    std::cout << "       BENCHMARK COMPLETED\n";
    std::cout << "====================================\n";


    return 0;
}