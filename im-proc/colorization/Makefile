ROOT=../bcl

CFLAGS=-Wall -Wextra -std=c99 -I$(ROOT)/include
LDFLAGS=-L$(ROOT)/lib -lbcl
LDLIBS=-lm -lbcl

OBJ=fft.o
BIN=\
	colorization

all: $(BIN)

colorization:

clean:
	$(RM) $(OBJ) $(BIN) *.ppm

.PHONY: all clean
