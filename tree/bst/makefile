# BST modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = ../../

objects = bst.o log.o	\

cc = gcc

testBST : $(objects)
	cc -o testBST $(objects)

bst.o : bst.h
log.o 	: log.h

.PHONY : clean
clean:
	rm $(objects)

