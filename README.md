# 🚀 MODEL Project – Polynomial Multiplication Benchmark (C)

This project implements and benchmarks multiple polynomial multiplication algorithms in **C**, including classical and high-performance methods. It allows comparison of **speed and accuracy** for polynomials of various degrees and provides **MPFR-based high-precision results** as a reference.

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
make
./make.exe
```
> ⚠️ Note: **.exe** is just the executable name; it runs on all systems.

# 🧹 Clean (Optional)
```bash
make clean
```


# 📈 Output
The program prints:
1. Input polynomials
2. Multiplication results for all algorithms
3. Execution time for each algorithm
4. Maximum absolute error vs MPFR (for accuracy evaluation)
5. Best k parameter determined from timing benchmarks   

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

