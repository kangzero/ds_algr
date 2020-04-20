#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "log.h"
#include "linear/array/sorts.h"
#include "linear/bits/bits.h"
#include "linear/mem/alloc.h"
#include "linear/mem/mem.h"
#include "linear/mem/rbuffer.h"
#include "linear/list/slink/slink.h"
#include "linear/list/dlink/dlink.h"
#include "linear/list/staticlist/staticlist.h"
#include "linear/stack/array_stack.h"
#include "linear/stack/slink_stack.h"
#include "linear/stack/dlink_stack.h"
#include "linear/queue/array_queue.h"
#include "linear/queue/slink_queue.h"
#include "linear/queue/dlink_queue.h"
#include "tree/bst/bst.h"

extern int slink_test(void);
extern int dlink_test(void);

typedef enum {
    Array = 1,
    Bits,
    String,
    Linkedlist,
    Memory,
    Stack,
    Queue
} Modules;

int main(int argc, char* argv[])
{
    logger_init();

    array_sorting_test();
    bits_test();
    buffer_alloc_free_test();
    nk_malloc_free_test();
    mem_test();
    ring_buffer_test();
    slink_test();
    dlink_test();
    static_list_test();
    array_stack_test();
    slink_stack_test();
    dlink_stack_test();
    array_queue_test();
    slink_queue_test();
    dlink_queue_test();

    bst_test();

    return 1;
}
