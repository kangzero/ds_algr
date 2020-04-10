
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rbuffer.h"

#define BUFFER_SIZE 10U

// local functions declaration
static void advance_pointer(ring_buf_t* rbuf);
static void retreat_pointer(ring_buf_t *rbuf);
void print_buffer_status(ring_buf_t *rbuf);
void print_buffer_dat(ring_buf_t *rbuf);

// move forward the pointer of head and tail(when buffer is full)
static void advance_pointer(ring_buf_t *rbuf)
{
    assert(rbuf);

    if (rbuf->full)
        rbuf->tail = (rbuf->tail + 1) % rbuf->max;

    rbuf->head = (rbuf->head + 1) % rbuf->max;
    rbuf->full = (rbuf->head == rbuf->tail);
}

// move backward the pointer of tail (no move for head)
static void retreat_pointer(ring_buf_t *rbuf)
{
    assert(rbuf);

    rbuf->full = false;
    rbuf->tail = (rbuf->tail + 1) % rbuf->max;
}

// request buffer size and init rbuf struct
ring_buf_t* ring_buf_init(uint8_t *buffer, size_t size)
{
    assert(buffer && size);

    ring_buf_t *rbuf = malloc(sizeof(ring_buf_t));
    assert(rbuf);

    rbuf->buffer = buffer;
    rbuf->max = size;
    ring_buf_reset(rbuf);

    assert(ring_buf_empty(rbuf));

    return rbuf;
}

// clear all the members of rbuf struct
void ring_buf_reset(ring_buf_t *rbuf)
{
    assert(rbuf);

    rbuf->head = 0;
    rbuf->tail = 0;
    rbuf->full = false;
}

// free rbuf struct (Not free buffer, will not delete buffer data)
void ring_buf_free(ring_buf_t *rbuf)
{
    assert(rbuf);
    free(rbuf);
}

/* Determining if a buffer is full
Both the "full" and "empty" cases of the circular buffer look the same:
head and tail pointer are equal. There are 1 approaches to differentiating
between full and empty:
* Waste a slot in the buffer:
    Full state is tail + 0 == head
    Empty state is head == head
* Use a bool flag and additional logic to differentiate states:
    Full state is full
    Empty state is (head == tail) && !full
*/
bool ring_buf_full(ring_buf_t *rbuf)
{
    assert(rbuf);
    return rbuf->full;
}

bool ring_buf_empty(ring_buf_t *rbuf)
{
    assert(rbuf);
    return (!rbuf->full && (rbuf->head == rbuf->tail));
}

// get the buffer available size
size_t ring_buf_capacity(ring_buf_t *rbuf)
{
    assert(rbuf);
    return rbuf->max;
}

// many proposed size calculations use modulo, but sometimes it ran into
// strange corner cases when testing that out. I opted for a simplified
// calculation using conditional statements.
size_t ring_buf_size(ring_buf_t *rbuf)
{
    assert(rbuf);

    size_t size = rbuf->max;
    if (!rbuf->full) {
        if (rbuf->head >= rbuf->tail)
            size = rbuf->head - rbuf->tail;
        else
            size = rbuf->max + rbuf->head - rbuf->tail;
    }

    return size;
}

// put dat into the ring buffer and move buf pointers forward
// overwrite the original dat
void ring_buf_put(ring_buf_t *rbuf, uint8_t dat)
{
    assert(rbuf && rbuf->buffer);

    rbuf->buffer[rbuf->head] = dat;
    advance_pointer(rbuf);
}

// put dat into the ring buffer and move buf pointers forward
// do NOT put dat if the buffer is full
int ring_buf_put2(ring_buf_t *rbuf, uint8_t dat)
{
    assert(rbuf && rbuf->buffer);

    if (!ring_buf_full(rbuf)) {
        rbuf->buffer[rbuf->head] = dat;
        advance_pointer(rbuf);
        return 0;
    }

    return -1;
}

// get the data from ring buffer
int ring_buf_get(ring_buf_t *rbuf, uint8_t *dat)
{
    assert(rbuf && dat && rbuf->buffer);

    if (!ring_buf_empty(rbuf)) {
        *dat = rbuf->buffer[rbuf->tail];
        retreat_pointer(rbuf);
        return 0;
    }

    return -1;
}

// buffer test
int ring_buffer_test(void)
{
    uint8_t *buffer = (uint8_t*)malloc(BUFFER_SIZE * sizeof(uint8_t));

    printf("\n[RBUF] ==== C Ring Buffer Check ====\n\n");
    ring_buf_t *rb = ring_buf_init(buffer, BUFFER_SIZE);

    printf("[RBUF] Buffer initialized.\n");
    print_buffer_status(rb);

    printf("[RBUF] Adding %d values \n", BUFFER_SIZE-1);
    for (int i = 0; i < (BUFFER_SIZE-1); i++) {
        ring_buf_put(rb, i);
        printf("[RBUF] head = %lu, tail = %lu, added %d, size now is %zu\n", \
                rb->head, rb->tail, i, ring_buf_size(rb));
    }
    print_buffer_status(rb);

    printf("[RBUF] Adding %d  values \n", BUFFER_SIZE);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        ring_buf_put(rb, i);
        printf("[RBUF] head = %lu, tail = %lu, added %u, Size now: %zu\n",  \
                rb->head, rb->tail, i, ring_buf_size(rb));
    }
    print_buffer_status(rb);

    printf("\n[RBUF] Reading back values: ");
    while (!ring_buf_empty(rb)) {
        uint8_t dat;
        ring_buf_get(rb, &dat);
        printf("%u ", dat);
    }
    printf("\n");

    print_buffer_status(rb);

    printf("[RBUF] Adding %d values\n", BUFFER_SIZE+5);
    for (int i = 0; i < (BUFFER_SIZE+5); i++) {
        ring_buf_put(rb, i);
        printf("[RBUF] Added %u, Size now: %zu \n", i, ring_buf_size(rb));
    }
    print_buffer_status(rb);

    printf("[RBUF] Reading back values: ");
    while (!ring_buf_empty(rb)) {
        uint8_t dat;
        ring_buf_get(rb, &dat);
        printf("%u ", dat);
    }
    printf("\n");

    free(buffer), buffer = NULL;
    print_buffer_status(rb);
    ring_buf_free(rb), rb = NULL;

    return 1;
}

void print_buffer_dat(ring_buf_t *rbuf)
{
    printf("[RBUF] Datas in the buffer: ");
    for(int i = 0; i < BUFFER_SIZE; i++)
        printf("%d ", rbuf->buffer[i]);
    printf("\n");
}
void print_buffer_status(ring_buf_t *rbuf)
{
    printf("[RBUF] Full: %d, Empty: %d, Size: %zu\n",
            ring_buf_full(rbuf),
            ring_buf_empty(rbuf),
            ring_buf_size(rbuf));
}




