CFLAGS += -D _FULL_SYS

VPATH = array/ \
		bits/ \
		mem/ \
		list/ \
		list/slink \
		list/dlink \
		list/staticlist \
		stack/

objects = main.o common.o log.o \
		  array/sorts.o \
		  bits/bits.o \
		  mem/alloc.o mem/mem.o mem/rbuffer.o \
		  list/list_test.o list/list_api.o 	\
		  list/slink/slink.o list/dlink/dlink.o \
		  list/staticlist/staticlist.o \
		  stack/array_stack.o stack/slink_stack.o stack/dlink_stack.o \

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
slink.o 	: slink.h
dlink.o 	: dlink.h 
staticlist.o: staticlist.h
list_api.o 	: list_api.h 
list_test.o : list_test.c
array_stack.o : array_stack.h
slink_stack.o : slink_stack.h
dlink_stack.o : dlink_stack.h

.PHONY : clean
clean: 
	rm  $(objects)
