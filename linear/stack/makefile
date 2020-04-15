# stack modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = ../ 

objects = array_stack.o ../log.o	\

cc = gcc

testStack : $(objects)
	cc -o testStack $(objects)

array_stack.o : array_stack.h
log.o 	: log.h

.PHONY : clean
clean:
	rm $(objects)

