#include "CpuBenchmark.h"

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>


// Constructor
CpuBenchmark::CpuBenchmark()
{
}


// Get logical CPU thread count
unsigned int CpuBenchmark::getCpuThreads() const
{
    return std::thread::hardware_concurrency();
}


// CPU-intensive calculation
uint64_t CpuBenchmark::calculate(uint64_t start,
                                 uint64_t iterations)
{
    uint64_t value = start;

    for (uint64_t i = 0; i < iterations; ++i)
    {
        value ^= value >> 12;
        value ^= value << 25;
        value ^= value >> 27;

        value *= 2685821657736338717ULL;
    }

    return value;
}


// Run CPU benchmark
void CpuBenchmark::runBenchmark(
    unsigned int threadCount,
    uint64_t totalIterations)
{
    std::vector<std::thread> workers;

    std::vector<uint64_t> results(threadCount);

    // Distribute workload between threads
    uint64_t iterationsPerThread =
        totalIterations / threadCount;

    uint64_t remaining =
        totalIterations % threadCount;


    // Start timer
    auto start = std::chrono::high_resolution_clock::now();


    // Create threads
    for (unsigned int i = 0; i < threadCount; ++i)
    {
        uint64_t iterations = iterationsPerThread;

        if (i < remaining)
            ++iterations;

        workers.emplace_back(
            [i, iterations, &results]()
            {
                results[i] = calculate(
                    123456789ULL + i,
                    iterations
                );
            }
        );
    }


    // Wait for all threads
    for (auto& worker : workers)
    {
        worker.join();
    }


    // Stop timer
    auto stop = std::chrono::high_resolution_clock::now();


    // Calculate execution time
    double elapsed =
        std::chrono::duration<double>(stop - start).count();


    // Calculate speed
    double speed =
        static_cast<double>(totalIterations) / elapsed;


    // Prevent results from being unused
    uint64_t checksum = 0;

    for (uint64_t result : results)
        checksum ^= result;


    // Display results
    std::cout << std::left
              << std::setw(12) << threadCount
              << std::setw(18) << std::fixed
              << std::setprecision(4) << elapsed
              << std::setw(22) << std::fixed
              << std::setprecision(2) << speed
              << checksum
              << '\n';
}