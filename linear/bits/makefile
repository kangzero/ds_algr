CFLAGS += -D _MODULAR_TEST
VPATH = bits : ../includes

objects = bits.o common.o \

cc = gcc

testBits : $(objects)
		cc -o testBits $(objects)

bits.o : bits.h
common.o : common.h

.PHONY : clean
clean:
	rm $(objects)

