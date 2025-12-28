# 🚀 MODEL Project – Polynomial Multiplication Benchmark (C)

This project implements and benchmarks multiple polynomial multiplication algorithms in **C**, including classical and high-performance methods. It is designed to help compare **speed and accuracy** for polynomials of various degrees.

---

## 📚 Algorithms Covered
1. **Naive Classical Multiplication**  
2. **Karatsuba Multiplication**  
3. **Toom-Cook Multiplication**  
4. **Toom-4 Multiplication**  
5. **Naive Multiplication using MPFR library** ([MPFR](https://www.mpfr.org/)) for high-precision computations  

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
    Define your polynomials in main.c. Example polynomials are already provided.

2. Run the Algorithms:
    main.c is the driver that runs all algorithms on the defined polynomials. Each algorithm is implemented in its respective .h file.

3. Benchmark and Compare:
    Execution time is measured for each algorithm. 
    Results are printed in a readable polynomial format.
    High-precision results are computed with the MPFR library for comparison.

4. Adjust Parameters:
    For Karatsuba, Toom-Cook, and Toom-4, adjust the k parameter to see its impact on performance.


# 🏗️ Build and Run
```bash
make
./make.exe
```


# 🧹 Clean (Optional)
```bash
make clean
```


# 📈 Output
The program prints:
1. Input polynomials
2. Multiplication results for all algorithms
3. Execution time for each method
4. Best k parameter determined from timing benchmarks

# 🎯 Purpose
This project allows you to:
1. Compare efficiency of polynomial multiplication algorithms.
2. Evaluate accuracy of double-precision vs. high-precision (MPFR) calculations.
3. Understand how advanced algorithms like Karatsuba and Toom-Cook optimize large polynomial multiplications.


