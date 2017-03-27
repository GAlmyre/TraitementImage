ROOT=../bcl

CFLAGS=-Wall -Wextra -Werror -std=c99 -I$(ROOT)/include
LDFLAGS=-L$(ROOT)/lib
LDLIBS=-lm -lbcl

OBJ=morphology.o

BIN=\
	make-se\
	labeling\
	erosion\
	dilatation\
	opening\
	closing\
	add\
	substract\
	binarize\
	labeling-color

all: $(BIN)

make-se: morphology.o

erosion: morphology.o

dilatation: morphology.o

opening: morphology.o

closing: morphology.o

add: morphology.o

substract: morphology.o

binarize: morphology.o

clean:
	$(RM) $(OBJ) $(BIN) *.ppm

.PHONY: all clean
