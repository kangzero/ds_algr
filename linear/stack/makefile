# stack modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = ../   ../list/slink/ 

objects = array_stack.o \
		  slink_stack.o \
		  ../list/slink/slink.o \
		  ../log.o	\

cc = gcc

testStack : $(objects)
	cc -o testStack $(objects)

array_stack.o : array_stack.h
slink_stack.o : slink_stack.h
slink.o : slink.h
log.o 	: log.h

.PHONY : clean
clean:
	rm $(objects)

