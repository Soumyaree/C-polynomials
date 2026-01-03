# MODEL Project: Polynomial Multiplication
This project implements and benchmarks multiple polynomial multiplication algorithms in C. It compares performance and accuracy for polynomials of various degrees. The naive polynomial multiplication algorithm is used as a reference.

## Algorithms covered
This Project contains .h files for each algorithm and main.c as the main driver file to run all those algorithms
1. **Naive Classical Multiplication**  
2. **Karatsuba Multiplication**  
3. **Toom-Cook Multiplication**  
4. **Toom-4 Multiplication**  
5. **Naive Multiplication using MPFR library** ([MPFR](https://www.mpfr.org/)) for high-precision computations  

## Code Structure
1. Each multiplication algorithm is implemented in its respective .c / .h file.
2. Main.c imports and runs all algorithms, prints the results, and calculates the time cost.
3. Execution time is measured for each algorithm.
4. Karatsuba, Toom-Cook, and Toom-4 allow adjusting the k parameter to optimize performance.
5. Outputs include results, execution times, and accuracy comparison vs MPFR.

# Build and Run
```bash
make
./make.exe
```

# Output
The program prints:
1. Input polynomials
2. Multiplication results for all algorithms
3. Execution time for each algorithm
4. Maximum absolute error vs MPFR (for accuracy evaluation)
