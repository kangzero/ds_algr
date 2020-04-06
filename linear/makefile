CFLAGS += -D _FULL_SYS

objects = main.o includes/common.o bits/bits.o 

cc = gcc

linear : $(objects)
	cc -o testMain $(objects)

main.o : main.c 
	cc -c $^
bits.o : bits/bits.c bits/bits.h ../includes/common.h 
	cc -c $^
common.o : includes/common.c includes/common.h 
	cc -c $^

.PHONY : clean
clean: 
	rm  $(objects)

