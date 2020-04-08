
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ringbuffer.h"

#define BUFFER_SIZE 10U

static void advance_pointer(ring_buf_t *rbuf)
{
    assert(rbuf);

    if (rbuf->full)
        rbuf->tail = (rbuf->tail + 1) % rbuf->max;

    rbuf->head = (rbuf->head + 1) % rbuf->max;
    rbuf->full = (rbuf->head == rbuf->tail);
}

static void retreat_pointer(ring_buf_t *rbuf)
{
    assert(rbuf);

    rbuf->full = false;
    rbuf->tail = (rbuf->tail + 1) % rbuf->max;
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

void ring_buf_reset(ring_buf_t *rbuf)
{
    assert(rbuf);

    rbuf->head = 0;
    rbuf->tail = 0;
    rbuf->full = false;
}

void ring_buf_free(ring_buf_t *rbuf)
{
    assert(rbuf);
    free(rbuf);
}

bool ring_buf_empty(ring_buf_t *rbuf)
{
    assert(rbuf);
    return (!rbuf->full && (rbuf->head == rbuf->tail));
}

bool ring_buf_full(ring_buf_t *rbuf)
{
    assert(rbuf);
    return rbuf->full;
}

size_t ring_buf_capacity(ring_buf_t *rbuf)
{
    assert(rbuf);
    return rbuf->max;
}

//many proposed size calculations use modulo, but sometimes it ran into
//strange corner cases when testing that out. I opted for a simplified
//calculation using conditional statements.
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


void ring_buf_put(ring_buf_t *rbuf, uint8_t dat)
{
    assert(rbuf && rbuf->buffer);

    rbuf->buffer[rbuf->head] = dat;
    advance_pointer(rbuf);
}

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

void print_buffer_status(ring_buf_t *rbuf);
void print_buffer_dat(ring_buf_t *rbuf);


void main(void)
{
    uint8_t *buffer = malloc(BUFFER_SIZE * sizeof(uint8_t));

    printf("\n === C Ring Buffer Check === \n");
    ring_buf_t *rbuf_h = ring_buf_init(buffer, BUFFER_SIZE);

    printf("Buffer initialized.");
    print_buffer_status(rbuf_h);

    printf("\n ****** \n Adding %d  values \n", BUFFER_SIZE-1);
    for (int i = 0; i < (BUFFER_SIZE-1); i++) {
        ring_buf_put(rbuf_h, i);
        //printf("111 - head = %lu, tail = %lu\n", rbuf_h->head, rbuf_h->tail);
        printf("Added %u, Size now: %zu\n", i, ring_buf_size(rbuf_h));
    }
    print_buffer_status(rbuf_h);

    printf("\n ****** \n Adding %d  values \n", BUFFER_SIZE);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        ring_buf_put(rbuf_h, i);
        printf("Added %u, Size now: %zu\n", i, ring_buf_size(rbuf_h));
    }
    print_buffer_status(rbuf_h);

    //ring_buf_put(rbuf_h, 100);
    //printf("222 - head = %lu, tail = %lu\n", rbuf_h->head, rbuf_h->tail);
    //ring_buf_put(rbuf_h, 101);
    //printf("333 - head = %lu, tail = %lu\n", rbuf_h->head, rbuf_h->tail);
    //print_buffer_dat(rbuf_h);
    printf("\n ****** \n Reading back values:");
    while (!ring_buf_empty(rbuf_h)) {
        uint8_t dat;
        ring_buf_get(rbuf_h, &dat);
        printf("%u \n", dat);
    }
    printf("\n");

    print_buffer_status(rbuf_h);

    printf("\n ******\n Adding %d values\n", BUFFER_SIZE+5);
    for (int i = 0; i < (BUFFER_SIZE+5); i++) {
        ring_buf_put(rbuf_h, i);
        printf("Added %u, Size now: %zu \n", i, ring_buf_size(rbuf_h));
    }
    print_buffer_status(rbuf_h);


    printf("\n ****** \n Reading back values:");
    while (!ring_buf_empty(rbuf_h)) {
        uint8_t dat;
        ring_buf_get(rbuf_h, &dat);
        printf("%u ", dat);
    }
    printf("\n");

    free(buffer);
    print_buffer_status(rbuf_h);

    return;
}

void print_buffer_dat(ring_buf_t *rbuf)
{
    for(int i = 0; i < BUFFER_SIZE; i++)
        printf("%d ", rbuf->buffer[i]);
    printf("\n");
}
void print_buffer_status(ring_buf_t *rbuf)
{
    printf("Full: %d, Empty: %d, Size: %zu\n",
            ring_buf_full(rbuf),
            ring_buf_empty(rbuf),
            ring_buf_size(rbuf));
}




