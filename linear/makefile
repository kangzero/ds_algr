CFLAGS += -D _FULL_SYS
VPATH = array/ \
		bits/ \
		mem/ \
		list/ \
		list/slink \

objects = main.o common.o log.o \
		  array/sorts.o \
		  bits/bits.o \
		  mem/alloc.o mem/mem.o mem/rbuffer.o \
		  list/slink_test.o \
		  list/list_api.o 	\
		  list/slink/slink.o \

cc = gcc

testMain : $(objects)
	cc -o testMain $^

main.o 			: main.c 
#	cc -c $^
log.o 			: log.h 
sorts.o 		: sorts.h 
#	cc -c $^
bits.o 			: bits.h common.h
#	cc -c $^
common.o 		: common.h 
#	cc -c $^
alloc.o 		: alloc.h
#	cc -c $^
mem.o 			: mem.h 
#	cc -c $^
rbuffer.o 		: rbuffer.h
#	cc -c $^
slink.o 	: slink.h 
list_api.o 		: list_api.h 
slink_test.o 	: slink_test.c

.PHONY : clean
clean: 
	rm  $(objects)
