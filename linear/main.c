#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "log.h"
#include "array/sorts.h"
#include "bits/bits.h"
#include "mem/alloc.h"
#include "mem/mem.h"
#include "mem/rbuffer.h"
#include "list/slink/slink.h"
#include "list/dlink/dlink.h"
#include "list/staticlist/staticlist.h"

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

    return 1;
}
