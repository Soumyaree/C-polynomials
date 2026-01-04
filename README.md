![Commit](https://img.shields.io/badge/Polynomials-C-blue)

# 🚀 MODEL Project – Polynomial Multiplication Benchmark (C)

This project implements and benchmarks multiple polynomial multiplication algorithms in **C**, including classical and high-performance methods. It allows comparison of **speed and accuracy** for polynomials of various degrees and provides **MPFR-based high-precision results** as a reference.

This project is also builded and tested multiple times in jenkins which executes demo mode, benchmark mode, and CI execution with Jenkins.

---


## 📚 Algorithms Covered
1. **Naive Classical Multiplication**  
2. **Karatsuba Multiplication**  
3. **Toom-Cook Multiplication**  
4. **Toom-4 Multiplication**  
5. **Naive Multiplication using MPFR library** ([MPFR](https://www.mpfr.org/)) for high-precision computations  

> MPFR results serve as a **reference solution** to evaluate numerical stability and accuracy of double-precision algorithms.

---

## 🛠️ Prerequisites

### On macOS
```bash
brew install gcc gmp mpfr
```

## On Debian-based systems / WSL
```bash
apt install build-essential libgmp-dev libmpfr-dev
```

## ⚡ Procedure / How It Works

1. Prepare Polynomials:
    Random or predefined polynomials are generated. Polynomials are stored in double precision.

2. Run the Algorithms:
    main.c is the driver. Each multiplication algorithm is implemented in its respective .c / .h file.

3. High-Precision Comparison:
    MPFR-based naive multiplication is called via a dedicated MPFR module.
        1. **Computes reference polynomial multiplication with 256-bit precision.**
        2. **Maximum absolute errors between double-precision and MPFR results are measured.**

4. Benchmark and Evaluate:
    1. **Execution time is measured for each algorithm.**
    2. **Karatsuba, Toom-Cook, and Toom-4 allow adjusting the k parameter to optimize performance.**
    3. **Outputs include results, execution times, and accuracy comparison vs MPFR.**


# 🏗️ Build and Run
```bash
# To run the full project from the bash script
chmod +x run.sh # this makes the bash file executable, use sudo if required
./run.sh
# or create the project manually
make
./make.exe
```
> ⚠️ Note: **.exe** is just the executable name; it runs on Unix-based systems as well.


# 🧹 Clean (Optional)
```bash
make clean
```

## This builds:
`main.exe` \
***(Bench executables are built separately when needed)***

# ▶️ Running the Program

## 1. Demo Mode (human-readable output)

```bash
./main.exe demo
```

## Displays:
1. Input polynomials
2. Results from each algorithm

## 2. Benchmark Mode (default)
```bash
./main.exe
```

# 🧪 Dedicated Benchmarks
**Each advanced algorithm has its own benchmark program:**
```shell
gcc src/bench_karatsuba.c ... -o bench_karatsuba.exe
gcc src/bench_toom_cook.c ... -o bench_toom_cook.exe
gcc src/bench_toom4.c ... -o bench_toom4.exe
```

## Jenkins Integration
1. Jenkins Pipeline Steps
2. Checkout source
3. Build using Makefile
4. Run demo mode
5. Run benchmark mode
6. Archive logs as artifacts

***These benchmarks:***
1. Explore optimal k values
2. Compare base cases (naive vs karatsuba)
3. Output timing data (CSV-friendly)

## Outputs:
1. Execution time per algorithm
2. Numerical error vs MPFR reference
3. Results for increasing polynomial degrees

# 🔬 Numerical Accuracy
1. Coefficients are random doubles in [-1, 1]
2. MPFR precision: 256 bits
3. Error metric: maximum absolute error
4. MPFR results are considered exact
5. As polynomial degree increases:
6. Double-precision errors grow slightly
7. Recursive algorithms (Karatsuba, Toom) accumulate rounding errors
8. MPFR remains perfectly stable

# 🎯 Purpose
This project allows you to:
1. Compare efficiency of polynomial multiplication algorithms.
2. Evaluate accuracy of double-precision vs. high-precision (MPFR) calculations.
3. Understand the speed and accuracy for large polynomial multiplications.
4. Optimize recursive algorithms using parameter k tuning (Karatsuba, Toom-Cook, Toom-4).


# 📌 Notes
1. MPFR is slower but exact; use it for validation and benchmarking.
2. Double-precision algorithms are fast but prone to rounding errors, especially for higher degrees.
3. This setup allows for quantitative study of error accumulation in different algorithms.



# References
***Go the links to find the reffs :*** \
[Polynomial multiplication](https://en.wikipedia.org/wiki/Polynomial_multiplication) \
[IEEE 754 floating-point](https://en.wikipedia.org/wiki/IEEE_754) \
[MPFR library](https://www.mpfr.org/) 

**Sources of [Icons](https://img.shields.io/) and github style emoji codes**

