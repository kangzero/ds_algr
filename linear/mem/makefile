# makefile for modular test 
CFLAGS += -D _MODULAR_TEST
VPATH = 

objects = alloc.o mem.o rbuffer.o 	\

cc = gcc

testMem : $(objects)
		cc -o testMem $(objects)

alloc.o 	: alloc.h
mem.o 		: mem.h
rbuffer.o 	: rbuffer.h

.PHONY : clean
clean:
	rm $(objects)

