CFLAGS += -D _FULL_SYS

objects = main.o common.o bits/bits.o mem/alloc.o

cc = gcc

linear : $(objects)
	cc -o testMain $(objects)

main.o : main.c 
	cc -c $^
bits.o : bits/bits.c bits/bits.h ../common.h 
	cc -c $^
common.o : common.c common.h 
	cc -c $^
alloc.o : mem/alloc.c mem/alloc.h
	cc -c $^

.PHONY : clean
clean: 
	rm  $(objects)

