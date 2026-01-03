# MODEL Project – Polynomial Multiplication Benchmark (C)
This project implements and benchmarks multiple polynomial multiplication algorithms in C, including classical and high-performance methods. It allows comparison of speed and accuracy for polynomials of various degrees. The naive double precision algorithm is used as a reference. 
At the same time, a report was written to analyze the algorithms, describe them in greater detail, and answer various questions.

## Algorithms covered
1. **Naive Classical Multiplication**  
2. **Karatsuba Multiplication**  
3. **Toom-Cook Multiplication**  
4. **Toom-4 Multiplication**  
5. **Naive Multiplication using MPFR library** ([MPFR](https://www.mpfr.org/)) for high-precision computations  

## Prerequisites

### On macOS
```bash
brew install gcc gmp mpfr
```

## On Debian-based systems / WSL
```bash
apt install build-essential libgmp-dev libmpfr-dev
```

## Procedure / How It Works

1. Prepare Polynomials:
    Random or predefined polynomials are generated. Polynomials are stored in double precision.

2. Run the Algorithms:
    main.c is the driver. Each multiplication algorithm is implemented in its respective .c / .h file.

3. High-Precision Comparison:
    MPFR-based naive multiplication is called via a dedicated MPFR module.
        1. Computes reference polynomial multiplication with 256-bit precision.
        2. Maximum absolute errors between double-precision and MPFR results are measured.

4. Benchmark and Evaluate:
    1. Execution time is measured for each algorithm.
    2. Karatsuba, Toom-Cook, and Toom-4 allow adjusting the k parameter to optimize performance, and allow to change the base-case to analyse the differences.
    3. Outputs include results, execution times, and accuracy comparison vs MPFR.

⚠️ Special feature: The benchmarks for the Karatsuba, Toom-Cook, and Toom4 algorithms take time to run. For this reason, we have placed them in separate files named bench_karatsuba.c, bench_ToomCook.c, and
bench_Toom4.c. To avoid any problems when launching the main program, they have been commented out. All results are given in the report. If you want to run a benchmark, you need to comment out the main program and uncomment the desired benchmark.


# Build and Run
```bash
make
./make.exe
```
> ⚠️ Note: **.exe** is just the executable name; it runs on all systems.

# Output
The program prints:
1. Input polynomials
2. Multiplication results for all algorithms
3. Execution time for each algorithm
4. Maximum absolute error vs MPFR (for accuracy evaluation)
