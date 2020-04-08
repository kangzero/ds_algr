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

    // we don't have any mem to manage yet, so set the beginning to be last_valid_address
    p_memory_start = last_valid_address;
    printf("p_memory_start :    %p\n\n", p_memory_start);

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

    size = align_up(size + sizeof(MCB), 4);
    //size = size + sizeof(MCB);
    mem_location = NULL;
    cur_location = p_memory_start;

    // keep going until we have searched all allocated space
    while (cur_location != NULL && cur_location != last_valid_address) {
        cur_location_mcb = (MCB*)cur_location;
        //printf("cur_location_mcb = %p, is_valid = %d, size = %u\n", cur_location_mcb, cur_location_mcb->is_valid, cur_location_mcb->size);
        if (cur_location_mcb->is_valid) {
            if (cur_location_mcb->size >= size) {
                // found an valid memory block and return the current address
                cur_location_mcb->is_valid = 0; // core dumped
                mem_location = cur_location;
                break;
            }
        }
        // move to next block to see if could grab an valid memory block
        cur_location = cur_location + cur_location_mcb->size;

    }
    if (mem_location == NULL)  {
        if (sbrk(size) == (void*)-1)
            return NULL;
        mem_location = last_valid_address;
        //printf("mem_location:           %p\n", mem_location);
        last_valid_address += size;
        //printf("last_valid_address:     %p\n", last_valid_address);
        cur_location_mcb = mem_location;
        cur_location_mcb->is_valid = 0;
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

    return;
}

// nk_malloc & nk_free test
int nk_malloc_free_test(void)
{
    nk__malloc_init();

    char *p1;
    if ((p1 = nk_malloc(100)) == NULL)
        return -1;
    MCB *p1_mcb = (void*)p1 - sizeof(MCB);
    printf("p1: %p, block size: %u, block valid: %d\n", p1, p1_mcb->size, p1_mcb->is_valid);
    nk_free(p1);
    printf("After free: p1 block valid = %d\n", p1_mcb->is_valid);
    p1 = NULL;

    int *p2;
    if ((p2 = nk_malloc(20)) == NULL)
        return -1;
    MCB *p2_mcb = (void*)p2 - sizeof(MCB);
    printf("p2: %p, block size: %u, block valid: %d\n", p2, p2_mcb->size, p2_mcb->is_valid);
    nk_free(p2);
    printf("After free: p2 block valid = %d\n", p2_mcb->is_valid);
    p2 = NULL;

    char *p3, *p4;
    if ((p3 = nk_malloc(100)) == NULL)
        return -1;
    MCB *p3_mcb = (void*)p3 - sizeof(MCB);
    printf("p3: %p, block size: %u, block valid: %d\n", p3, p3_mcb->size, p3_mcb->is_valid);
    if ((p4 = nk_malloc(1)) == NULL)
        return -1;
    MCB *p4_mcb = (void*)p4 - sizeof(MCB);
    printf("p4: %p, block size: %u, block valid: %d\n", p4, p4_mcb->size, p4_mcb->is_valid);
    nk_free(p4);
    p4 = NULL;
    printf("After free: p4 block valid = %d\n", p4_mcb->is_valid);

    int *p5;
    if ((p5 = nk_malloc(1000)) == NULL)
        return -1;
    MCB *p5_mcb = (void*)p5 - sizeof(MCB);
    printf("p5: %p, block size: %u, block valid: %d\n", p5, p5_mcb->size, p5_mcb->is_valid);
    nk_free(p3);;
    p3 = NULL;
    nk_free(p5);
    p5 = NULL;

    printf("\n\
    p1 block size: %10u   p1 block is_valid: %d \n\r\
    p2 block size: %10u   p2 block is_Valid: %d \n\r\
    p3 block size: %10u   p3 block is_Valid: %d \n\r\
    p4 block size: %10u   p4 block is_Valid: %d \n\r\
    p5 block size: %10u   p5 block is_Valid: %d \n\r\n",\
    p1_mcb->size, p1_mcb->is_valid,\
    p2_mcb->size, p2_mcb->is_valid,\
    p3_mcb->size, p3_mcb->is_valid,\
    p4_mcb->size, p4_mcb->is_valid,\
    p5_mcb->size, p5_mcb->is_valid);

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
    if (nk_malloc_free_test() == -1)
        printf("Error: your malloc failed!\n");

    return 1;
}
#endif








