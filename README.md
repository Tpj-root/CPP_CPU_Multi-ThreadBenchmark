# CPP_CPU_Multi-ThreadBenchmark




build

```
g++ -std=c++17 -O2 -pthread \
main.cpp CpuBenchmark.cpp \
-o CPU_Benchmark

```









Your results are interesting! Your Intel i3-3220 is showing good parallel processing behaviour, but there is an important detail: more software threads do not necessarily mean more computing power.

Let's analyze your actual results.

# 1. Your PC benchmark results

Best measured throughput in this run

# 1.101 billion

Iterations per second · 32 software threads

# 2

Physical cores

# 4

Logical processors

# 256

Maximum tested software threads

# 0.0454 s

Fastest measured time

## Performance comparison

| Threads | Time (sec) | Performance |
| ------- | ---------- | ----------- |
| 1       | 0.14632    | 341.7M      |
| 2       | 0.07260    | 688.7M      |
| 3       | 0.05215    | 958.7M      |
| 4       | 0.05718    | 874.4M      |
| 6       | 0.04802    | 1,041.2M    |
| 8       | 0.04910    | 1,018.3M    |
| 12      | 0.05022    | 995.6M      |
| 16      | 0.04919    | 1,016.5M    |
| 32      | 0.04540    | 1,101.4M    |
| 64      | 0.04833    | 1,034.6M    |
| 128     | 0.05262    | 950.2M      |
| 256     | 0.08290    | 603.1M      |

Your measured throughput for each software thread count.

0M300M600M900M1.2KM12346812163264128256

Important observation: 32 threads won this particular run, but that does not mean your CPU has 32 processing cores or that 32 is its optimal thread count. Your 4-thread measurement was slower than your 3-thread measurement, too. This variation can come from CPU scheduling, frequency changes, background processes and short benchmark duration.

Also, your test measures a specific integer calculation, not every kind of CPU workload.

# 2. Why can 32 software threads work on a 4-thread CPU?

Think of your CPU as a factory.

[smart industrial factory in a flat style with workers, robots and assembly line packing](https://images.openai.com/static-rsc-4/0VcTY3uLMTQk4kGc9qaDAQE-g6qoLJ8qO8OXPpkBxuiNJ5UvKTXL0QE6C6TZ49-qChAHCQqsasSS-DqCyyRV5NV602uCe1oOA3B1-SdzDbrVK9lSTygVIOGf3hFaGM6wgZcSD7o-KdxO_AGMsoOpZXYF08Y37c_nCTdpLK_g1q-gMsmDZmO5g6Lr4AnK60Eh?purpose=inline)

- Physical cores = 2 production machines.
- Logical processors = 4 execution schedules.
- Software threads = workers waiting to use the machines.

You can hire 32 workers, but you still have only 2 physical cores.

The operating system schedules those workers onto the available logical processors.

This is called time-sharing and thread scheduling.

When 256 threads are created, the system spends more time managing and scheduling work, and thread creation itself adds overhead.

# 3. What mathematical problems can your PC solve?

Your i3-3220 can solve many kinds of mathematical problems. There is no single maximum mathematical problem size: it depends on the algorithm, memory, precision and time available.

Here are some practical categories.

## 4. Mathematical workloads you can run

| Mathematical problem       | What your CPU can do                    | Difficulty           |
| -------------------------- | --------------------------------------- | -------------------- |
| Addition / multiplication  | Billions of simple operations           | Easy                 |
| Prime number search        | Search millions of numbers              | Easy–medium          |
| Fibonacci                  | Calculate large sequences               | Medium               |
| Matrix multiplication      | Multiply large matrices                 | Medium–hard          |
| Monte Carlo simulation     | Millions of random simulations          | Medium               |
| Numerical integration      | Calculate complex integrals numerically | Medium               |
| Differential equations     | Simulate physical systems               | Hard                 |
| FFT                        | Signal and frequency analysis           | Hard                 |
| Neural network inference   | Small models and numerical operations   | Depends on RAM/model |
| Cryptographic calculations | Hashing and integer arithmetic          | Medium–hard          |

## 5. How large a mathematical problem?

For example, matrix multiplication.

Suppose you multiply two square matrices:

\\[ C=A\times B \\]

For an \\(N\times N\\) matrix, ordinary matrix multiplication requires approximately:

\\[ 2N^3-N^2 \\]

floating-point operations.

[Notes for AHL 1.14—Introduction to matrices - IB](https://images.openai.com/static-rsc-4/A76HpSAn3bC2a6N6kzzJ7huSENVEDmwFnkIu8KRsPK6QV9xuZE2YYjcnebSDJDG80ft91m4VezoVxLMkOGCCGY3ZYlYqen7zpBZNE8cA70GMd84ruByidNDmNoMNnHeI38UdjZKi3sJdmiFiyO7W3XTJi-38wqolyPkSVK2_MWk?purpose=inline)

[revisiondojo.com](https://www.revisiondojo.com/ib/ib-math-ai/ai-ahl-1-14-introduction-to-matrices/notes?utm_source=chatgpt.com)

Some examples:

| Matrix size   | Approximate operations |
| ------------- | ---------------------- |
| 100 × 100     | 2 million              |
| 500 × 500     | 250 million            |
| 1,000 × 1,000 | 2 billion              |
| 2,000 × 2,000 | 16 billion             |
| 5,000 × 5,000 | 250 billion            |

Your processor can calculate these, but larger matrices need more memory and execution time.

For two double-precision input matrices and one output matrix:

\\[ Memory=3N^2\times8\text{ bytes} \\]

For a 5,000 × 5,000 example, that is approximately 572 MiB just for the three matrices.

## 6. What is the real limitation of your PC?

Your processor is an older 2012-era CPU. Its limitations are:

1. Only 2 physical cores.
2. Only 4 logical processors.
3. Lower memory bandwidth than modern processors.
4. No modern AVX2 instruction support.
5. Limited single-core performance compared with modern CPUs.

However, it is perfectly capable of learning and experimenting with parallel computing, numerical mathematics, simulations and C++ multithreading.

## 7. My recommended next experiment

I suggest building a mathematical CPU benchmark suite with these five tests:

[Primality Testing Algorithms. Authors: Shruti Singh, Akash Sinha… | by Shruti Singh | Medium](https://images.openai.com/static-rsc-4/64zB5jaFRwpYuZ6tQ0_lAFSmTHHsCKkq9d_b-0vxTdyKAqvGKNgOzRZogldNRiCDm-PlzyXkmbzmrZ880_v_7U0R4SYjRFcdSsJYUb8QXtjq2KEZZX91CxZ6kfACfeiXwUTtuHghV7zjy7jU6-E8MQOC4K0fVg4yKTZ3AWubTJg?purpose=inline)

1\. Prime number calculation

Find prime numbers from 1 to 100 million.

2\. Matrix multiplication

Test 500 × 500, 1000 × 1000 and larger matrices.

[Introduction to Monte Carlo simulations](https://images.openai.com/static-rsc-4/V5WfVC5QTKz2zOQHuEfvDPK18asTUjcY3WXKlBMNahs5MUpz0wIEDpuAIkmFZ63M8BvqSVvJW9DbJQZgTK6oN0gvAQRuIwMLyACk00RqmmsXLW2VYnT580OprO1ZlrGzeHitQBo4USwfVx-k8omNLEZWuM123AoX-NaJ6q5T3zM?purpose=inline)

3\. Monte Carlo simulation

Estimate Pi using millions of random points.

[The Fibonacci Sequence & Golden Ratio Worksheet (Nature's Code) - Key Included](https://images.openai.com/static-rsc-4/n4ciJs5n7NyzDmEipHU1ON15W2fqGhrbVMlLiM7lzQpWZFSyBPQ_WiKF9SrVhuLNMI9cGusA3Ih8FXgv2s70VBBLy0tbv9swc3AFLTBnwlZtGfqQj3DLmnxdTtzHGCfy_75K32SlbVqGJ19VVaG7YSIA0C_BR60o6keLDWQ4zrg?purpose=inline)

4\. Fibonacci calculation

Test big integer calculations.

[Numerical Solutions of ODEs with Python: Euler, Runge Kutta and Beyond | by Souvik Ta | Medium](https://images.openai.com/static-rsc-4/36Nm37dgoTC37D6UlIjmOpE3LEKQDhYZtd_S0QUrVKrzx-B0qlmbbidtkHJgDnB3Y5afg1usNso4-XW2tdTr5JWMZ3-XWamJOFVNBZ6vRpDEzmkpbdNW-QJYhG4R3k9M6gphHtN65DLm9UYBa0urnX4f8bfs32FawsCd9l9-HiU?purpose=inline)

5\. Numerical simulation

Solve differential equations numerically.

One important improvement: Before trusting your 32-thread result, increase benchmark duration to several seconds per test and repeat each test five times. Compare median execution times. Your current 0.045-second tests are too short to establish a reliable optimum.

My recommendation is to build this as a reusable C++ OOP mathematics benchmark library. It will teach you CPU architecture, algorithms, parallel processing, memory management and mathematical computation using your existing PC.