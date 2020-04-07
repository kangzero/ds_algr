#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mem.h"

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

// Buffer free - need free memory by reverse order
static void buffer_free(char* p_free)
{
    if (p_free >= Buf && p_free < Buf + MAX_SIZE_BUF) {
        available_buffer_size += (p_buf - p_free);
        p_buf = p_free;
    }
}

int main(int argc, char* argv[])
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

    return 1;
}








