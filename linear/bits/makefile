# bits module makefile
CFLAGS += -D _MODULAR_TEST
#VPATH = testBits : ../

objects = bits.o ../common.o \

cc = gcc

testBits : $(objects)
		cc -o testBits $(objects)

bits.o : bits.h
common.o : common.h

.PHONY : clean
clean:
	rm $(objects)

