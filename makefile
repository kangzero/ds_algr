

CFLAGS += -D _FULL_SYS

VPATH = linear/array/ \
		linear/bits/ \
		linear/mem/ \
		linear/list/ \
		linear/list/slink \
		linear/list/dlink \
		linear/list/staticlist \
		linear/stack/ \
		linear/queue/ \
		tree/bst/ \

objects = main.o common.o log.o \
		  linear/array/sorts.o \
		  linear/bits/bits.o \
		  linear/mem/alloc.o \
		  linear/mem/mem.o \
		  linear/mem/rbuffer.o \
		  linear/list/list_test.o \
		  linear/list/list_api.o 	\
		  linear/list/slink/slink.o \
		  linear/list/dlink/dlink.o \
		  linear/list/staticlist/staticlist.o \
		  linear/stack/array_stack.o \
		  linear/stack/slink_stack.o \
		  linear/stack/dlink_stack.o \
		  linear/queue/array_queue.o \
		  linear/queue/slink_queue.o \
		  linear/queue/dlink_queue.o \
		  tree/bst/bst.o \

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
array_queue.o : array_queue.h
slink_queue.o : slink_queue.h 
dlink_queue.o : dlink_queue.h 
bst.o 	: bst.h 

.PHONY : clean
clean: 
	rm  $(objects)
