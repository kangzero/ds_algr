#ifndef _RING_BUFFER_H_
#define _RIGN_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct ring_buf_t {
    uint8_t *buffer;
    size_t head;
    size_t tail;
    size_t max; //of the buffer
    bool full;
} ring_buf_t;

ring_buf_t* ring_buf_init(uint8_t *buffer, size_t size);
void ring_buf_free(ring_buf_t *rbuf);
void ring_buf_reset(ring_buf_t *rbuf);
//old data is overwritten if the buffer is full
void ring_buf_put(ring_buf_t *rbuf, uint8_t dat);
//return 0 on success, -1 if buffer is full
int ring_buf_put2(ring_buf_t *rbuf, uint8_t dat);
//return 0 on success, -1 if buffer is empty
int ring_buf_get(ring_buf_t *rbuf, uint8_t *dat);
bool ring_buf_empty(ring_buf_t *rbuf);
bool ring_buf_full(ring_buf_t *rbuf);
size_t ring_buf_capacity(ring_buf_t *rbuf);
size_t ring_buf_size(ring_buf_t *rbuf);

#endif
