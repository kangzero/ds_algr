# array modular test makefile

CFLAGS += -D _MODULAR_TEST

objects = sorts.o 	\

cc = gcc

testArray : $(objects)
	cc -o testArray $(objects)

sorts.o : sorts.h

.PHONY : clean
clean:
	rm $(objects)

