# makefile for modular test 
CFLAGS += -D _MODULAR_TEST
VPATH = 

objects = alloc.o \

cc = gcc

testBits : $(objects)
		cc -o testAlloc $(objects)

bits.o : alloc.h

.PHONY : clean
clean:
	rm $(objects)

