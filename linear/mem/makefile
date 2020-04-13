# makefile for modular test 
CFLAGS += -D _MODULAR_TEST
VPATH = 

objects = alloc.o mem.o rbuffer.o ../log.o	\

cc = gcc

testMem : $(objects)
		cc -o testMem $(objects)

alloc.o 	: alloc.h
mem.o 		: mem.h
rbuffer.o 	: rbuffer.h
log.o 		: ../log.h

.PHONY : clean
clean:
	rm $(objects)

