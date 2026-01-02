CC      = gcc
CFLAGS  = -O2 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS    = -lmpfr -lgmp

SRC = src/main.c \
      src/naive.c \
      src/karatsuba.c \
      src/toom_cook.c \
      src/toom_4.c \
      src/naive_mpfr.c \
      src/mpfr_compare.c

all:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) $(LIBS) -o main.exe

clean:
	rm -f main.exe
