#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "alloc.h"

//#define _BUFFER_ALLOC_FAILED_TEST
#define MAX_SIZE_BUF    1000U

static char Buf[MAX_SIZE_BUF] = {0};
static char* p_buf = Buf;
static uint32_t available_buffer_size = MAX_SIZE_BUF;


// Buffer alloc - need alloc memory by order
static void* buffer_alloc(size_t bytes)
{
    if ((Buf + MAX_SIZE_BUF - p_buf) >= bytes) {
        p_buf += bytes;
        return p_buf - bytes;
    }
    printf("Error: No enough available buffer to alloc! \n\n");
    return NULL;
}

// Buffer free - MUST free memory by reverse order
static void buffer_free(char* p_free)
{
    if (p_free >= Buf && p_free < Buf + MAX_SIZE_BUF) {
        available_buffer_size += (p_buf - p_free);
        p_buf = p_free;
    }
}

#define align_up(num, align)   (((num) + ((align) - 1)) & ~((align) - 1))    \

bool has_initialized = 0;
void *p_memory_start;
void *last_valid_address;

typedef struct mem_control_block {
    char is_valid;
    uint32_t size;
} MCB;

// malloc init
void nk__malloc_init(void)
{
    // grab the last valid address from OS
    last_valid_address = sbrk(0); // get the location of program break for 0 input
    printf("last_valid_address: %p\n", last_valid_address);
    // we don't have any mem to manage yet, so set the beginning to be last_valid_address
    p_memory_start = last_valid_address;
    // initialized flag
    has_initialized = 1;
    return;
}

// nk_malloc
void* nk_malloc(size_t size)
{
    // memory address we will return, set to 0 untill find suitable location
    void *mem_location;
    // hold where we are looking at in memory
    void *cur_location;
    // same as current_location, but cast to a mem_control_block
    MCB *cur_location_mcb;

    if (!has_initialized)
        nk__malloc_init();

    //size = align_up(size + sizeof(MCB), 4);
    size = size + sizeof(0);
    mem_location = NULL;
    cur_location_mcb = p_memory_start;
    // keep going until we have searched all allocated space
    while (cur_location != last_valid_address) {
        cur_location_mcb = (MCB*)cur_location;
        if (cur_location_mcb->is_valid) {
            if (cur_location_mcb->size >= size) {
                // found an valid memory block and return the current address
                cur_location_mcb->is_valid = 0; // core dumped
                mem_location = cur_location;
                break;
            }
            // move to next block to see if could grab an valid memory block
            cur_location = cur_location + cur_location_mcb->size;
        }
    }
    if (!mem_location) {
        if (sbrk(size) == (void*)-1)
            return NULL;
        mem_location = last_valid_address;
        last_valid_address += size;
        cur_location_mcb = mem_location;
        cur_location_mcb->is_valid = 0; // core dumped
        cur_location_mcb->size = size;
    }

    mem_location += sizeof(MCB);

    return mem_location;
}

// nk_free
void nk_free(void* p_free)
{
    MCB *mcb = p_free - sizeof(MCB);
    mcb->is_valid = 1;
    //mcb->size = 0;
    return;
}

// nk_malloc & nk_free test
int nk_malloc_free_test(void)
{
    printf("111\n");
    nk__malloc_init();
    printf("222\n");

    char *p1;
    if ((p1 = nk_malloc(100)) == NULL) {
        printf("sssssss\n");
        return -1;
    }
    printf("p1 = %p", p1);
    MCB *mcb = (void*)p1 - sizeof(MCB);
    printf("333\n");
    printf("%p, block size: %u, block valid: %d\n", p1, mcb->size, mcb->is_valid);
    nk_free(p1);
    printf("After free: block valid = %d\n", mcb->is_valid);
    p1 = NULL;

    return 1;
}

//buffer_alloc and buffer_free test
int buffer_alloc_free_test(void)
{
    printf("Buf address = %p\nAvailable size = %d\n", Buf, MAX_SIZE_BUF);
    printf("p_buf address = %p\nAvailable size = %d\n\n", p_buf, available_buffer_size);

    char* p1;
    if ((p1 = (char*)buffer_alloc(100*sizeof(char))) == NULL) {
        return -1;
    }
    available_buffer_size -= 100 * sizeof(char);
    printf("p1 address      : %p\n", p1);
    printf("p_buf address   : %p\n", p_buf);
    printf("Block size      : %lu\n", 100*sizeof(char));
    printf("Available size  : %d\n\n", available_buffer_size);

    uint32_t* p2;
    if ((p2 = (uint32_t*)buffer_alloc(20*sizeof(int))) == NULL) {
        return -1;
    }
    available_buffer_size -= 20 * sizeof(int);
    printf("p2 address      : %p\n", p2);
    printf("p_buf address   : %p\n", p_buf);
    printf("Block size      : %lu\n", 20*sizeof(int));
    printf("Available size  : %d\n\n", available_buffer_size);

    char* p3;
    if ((p3 = (char*)buffer_alloc(20*sizeof(char))) == NULL) {
        return -1;
    }
    available_buffer_size -= 20*sizeof(char);
    printf("p3 address      : %p\n", p3);
    printf("p_buf address   : %p\n", p_buf);
    printf("Block size      : %lu\n", 20*sizeof(char));
    printf("Available size  : %d\n\n", available_buffer_size);

    uint32_t* p4;
    if ((p4 = (uint32_t*)buffer_alloc(200*sizeof(int))) == NULL) {
        return -1;
    }
    available_buffer_size -= 200 * sizeof(int);
    printf("p4 address      : %p\n", p4);
    printf("p_buf address   : %p\n", p_buf);
    printf("Block size      : %lu\n", 200*sizeof(int));
    printf("Available size  : %d\n\n", available_buffer_size);

#ifdef _BUFFER_ALLOC_FAILED_TEST
    /*
    uint32_t* p5;
    if ((p5 = buffer_alloc(1*sizeof(int))) == NULL) {
        return -1;
    }*/
#endif
    buffer_alloc(1*sizeof(int)); //should use memory alloc as above, this this only for test

    buffer_free((void*)p4);
    p4 = NULL;
    printf("After release p4 block: \n");
    printf("p_buf address   : %p\n", p_buf);
    printf("Available size  : %d\n\n", available_buffer_size);
/*
    buffer_free((void*)p2);
    printf("Try to free memory by out-of-order...\n");
    printf("p_buf   : 0x%p\n", p_buf);
    printf("p2      : 0x%p\n", p2);
*/
    buffer_free((void*)p3);
    p3 = NULL;
    printf("After release p3 block: \n");
    printf("p_buf address   : %p\n", p_buf);
    printf("Available size  : %d\n\n", available_buffer_size);

    buffer_free((void*)p2);
    p4 = NULL;
    printf("After release p2 block: \n");
    printf("p_buf address   : %p\n", p_buf);
    printf("Available size  : %d\n\n", available_buffer_size);

    buffer_free((void*)p1);
    p4 = NULL;
    printf("After release p1 block: \n");
    printf("p_buf address   : %p\n", p_buf);
    printf("Available size  : %d\n\n", available_buffer_size);


}

#ifdef _MODULAR_TEST
int main(int argc, char* argv[])
{
    //printf("buffer_alloc & buffer_free test: \n");
    //buffer_alloc_free_test();

    printf("nk_malloc & nk_free test: \n");
    nk_malloc_free_test();

    return 1;
}
#endif








