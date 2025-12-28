CC = gcc
CFLAGS = -O2 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
SRC_DIR = src

SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/naive.c \
          $(SRC_DIR)/karatsuba.c \
          $(SRC_DIR)/toom_cook.c \
          $(SRC_DIR)/toom_4.c \
          $(SRC_DIR)/naive_mpfr.c

LIBS = -lmpfr -lgmp

all:
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) $(LIBS) -o main.exe

clean:
	rm -f main.exe
