CC      = gcc
CFLAGS  = -O2 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS    = -lmpfr -lgmp

COMMON_SRC = \
    src/naive.c \
    src/karatsuba.c \
    src/toom_cook.c \
    src/toom_4.c \
    src/naive_mpfr.c \
    src/mpfr_compare.c

all: main bench_karatsuba bench_toom_cook bench_toom4

main:
	$(CC) $(CFLAGS) src/main.c $(COMMON_SRC) $(LDFLAGS) $(LIBS) -o main.exe

bench_karatsuba:
	$(CC) $(CFLAGS) src/bench_karatsuba.c $(COMMON_SRC) $(LDFLAGS) $(LIBS) -o bench_karatsuba.exe

bench_toom_cook:
	$(CC) $(CFLAGS) src/bench_Toom_Cook.c $(COMMON_SRC) $(LDFLAGS) $(LIBS) -o bench_toom_cook.exe

bench_toom4:
	$(CC) $(CFLAGS) src/bench_Toom4.c $(COMMON_SRC) $(LDFLAGS) $(LIBS) -o bench_toom4.exe

clean:
	rm -f *.exe

