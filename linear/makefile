CFLAGS += -D _FULL_SYS

objects = main.o common.o array/sorts.o bits/bits.o \
		  mem/alloc.o mem/mem.o mem/rbuffer.o 	\

cc = gcc

testMain : $(objects)
	cc -o testMain $(objects)

main.o 		: main.c 
	cc -c $^
sorts.o 	: array/sorts.h 
	cc -c $^
bits.o 		: bits/bits.h ../common.h 
	cc -c $^
common.o 	: common.c common.h 
	cc -c $^
alloc.o 	: mem/alloc.h
	cc -c $^
mem.o 		: mem/mem.h 
	cc -c $^
rbuffer.o 	: mem/rbuffer.h
	cc -c $^

.PHONY : clean
clean: 
	rm  $(objects)
