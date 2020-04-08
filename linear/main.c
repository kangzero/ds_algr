#include <stdio.h>
#include <stdlib.h>
#include "bits/bits.h"
#include "mem/alloc.h"

int main(int argc, char* argv[])
{
    bits_test();
    buffer_alloc_free_test();
    nk_malloc_free_test();

    return 1;
}
