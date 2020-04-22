# AVL modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = ../../

objects = avl.o log.o	\

cc = gcc

testAVL : $(objects)
	cc -o testAVL $(objects)

avl.o : avl.h
log.o 	: log.h

.PHONY : clean
clean:
	rm $(objects)

