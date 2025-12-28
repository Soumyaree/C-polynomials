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
## Ro run it in Debian based system / WSL
```shell 
    apt install build-essential libgmp-dev libmpfr-dev
```

# Now the next step (Build and RUN) ---->
```shell
    make
    ./make.exe
    # please note:
    # the '.exe' file extention is just a name of the file which is executable;
    # it has nothing to do with DOS operated systems like Windows. You can execute this file from Unix based systems as well.
```

## clean main (optional)
<!-- If you want to clean the main you use this -->
```shell
    make clean
```