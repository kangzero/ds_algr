# array modular test makefile

CFLAGS += -D _MODULAR_TEST
VPATH = ../

objects = sorts.o log.o	\

cc = gcc

testArray : $(objects)
	cc -o testArray $(objects)

sorts.o : sorts.h
log.o 	: log.h

.PHONY : clean
clean:
	rm $(objects)

