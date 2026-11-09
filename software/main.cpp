
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <cstdint>
#include <numeric>

class CpuBenchmark
{
private:

    // CPU workload: perform repeated integer calculations
    static uint64_t calculate(uint64_t seed, uint64_t iterations)
    {
        uint64_t value = seed;

        for (uint64_t i = 0; i < iterations; ++i)
        {
            value ^= value >> 12;
            value ^= value << 25;
            value ^= value >> 27;

            value *= 2685821657736338717ULL;
        }

        return value;
    }


public:

    // Detect hardware logical processors
    unsigned int getHardwareThreads() const
    {
        return std::thread::hardware_concurrency();
    }


    // Benchmark a selected number of software threads
    void run(unsigned int threadCount, uint64_t totalIterations)
    {
        std::vector<std::thread> workers;
        std::vector<uint64_t> results(threadCount, 0);

        uint64_t perThread = totalIterations / threadCount;
        uint64_t remaining = totalIterations % threadCount;

        // Start timer
        auto start = std::chrono::steady_clock::now();

        // Create software threads
        for (unsigned int i = 0; i < threadCount; ++i)
        {
            uint64_t work = perThread + (i < remaining ? 1 : 0);

            workers.emplace_back([i, work, &results]()
            {
                results[i] = calculate(123456789ULL + i, work);
            });
        }

        // Wait for all threads to finish
        for (auto& worker : workers)
        {
            worker.join();
        }

        // Stop timer
        auto stop = std::chrono::steady_clock::now();

        // Calculate execution time
        double seconds =
            std::chrono::duration<double>(stop - start).count();

        // Calculate throughput
        double speed = totalIterations / seconds;

        // Calculate speedup compared with one thread
        uint64_t checksum = 0;

        for (uint64_t result : results)
        {
            checksum ^= result;
        }

        std::cout
            << std::left
            << std::setw(12) << threadCount
            << std::setw(16) << std::fixed
            << std::setprecision(5) << seconds
            << std::setw(22) << std::fixed
            << std::setprecision(0) << speed
            << checksum
            << '\n';
    }
};


int main()
{
    CpuBenchmark cpu;

    unsigned int hardwareThreads = cpu.getHardwareThreads();

    if (hardwareThreads == 0)
    {
        std::cout << "Cannot detect hardware threads.\n";
        return 1;
    }

    // Software thread counts to test
    std::vector<unsigned int> testThreads =
    {
        1, 2, 3, 4, 6, 8, 12, 16, 32, 64, 128, 256
    };

    // Total workload for every test
    uint64_t totalIterations = 50000000ULL;

    std::cout << "\n============================================\n";
    std::cout << "       C++ SOFTWARE THREAD BENCHMARK\n";
    std::cout << "============================================\n";

    std::cout << "\nHardware logical processors: "
              << hardwareThreads << '\n';

    std::cout << "Physical CPU cores: 2 (from your lscpu output)\n";

    std::cout << "Software thread tests: "
              << testThreads.size() << '\n';

    std::cout << "Total iterations per test: "
              << totalIterations << '\n';

    std::cout << "\n";

    std::cout << std::left
              << std::setw(12) << "Threads"
              << std::setw(16) << "Time (sec)"
              << std::setw(22) << "Iterations/sec"
              << "Checksum\n";

    std::cout << "-------------------------------------------------------------\n";

    for (unsigned int count : testThreads)
    {
        cpu.run(count, totalIterations);
    }

    std::cout << "\n============================================\n";
    std::cout << "           BENCHMARK COMPLETED\n";
    std::cout << "============================================\n";

    return 0;
}
