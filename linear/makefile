CFLAGS += -D _FULL_SYS
VPATH = array/ \
		bits/ \
		mem/ \
		linkedlist/ \
		linkedlist/singly_list \

objects = main.o common.o log.o \
		  array/sorts.o \
		  bits/bits.o \
		  mem/alloc.o mem/mem.o mem/rbuffer.o \
		  linkedlist/singly_list_test.o \
		  linkedlist/linkedlist_algorithms.o 	\
		  linkedlist/singly_list/singly_linkedlist.o \

cc = gcc

testMain : $(objects)
	cc -o testMain $^

main.o 		: main.c 
#	cc -c $^
log.o 		: log.h 
sorts.o 	: sorts.h 
#	cc -c $^
bits.o 		: bits.h common.h
#	cc -c $^
common.o 	: common.h 
#	cc -c $^
alloc.o 	: alloc.h
#	cc -c $^
mem.o 		: mem.h 
#	cc -c $^
rbuffer.o 	: rbuffer.h
#	cc -c $^
singly_list_test.o : singly_list_test.c
linkedlist_algorithms.o : linkedlist_algorithms.h 
singly_linkedlist.o 	:	singly_linkedlist.h 

.PHONY : clean
clean: 
	rm  $(objects)
