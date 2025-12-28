# model-project
MODEL Implementation Project (C)


This Project contains .h files for each algorithm and main.c as main driver file to run all those algorithms.
Algorithms Covered:
1. Naive Classical
2. Karatsuba
3. Took Cook
4. Toom - 4
5. Naive Algorithm using MPFR library (https://www.mpfr.org/)

# Pre-requisits --->

## To run it in mac
```shell 
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