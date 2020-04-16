#ifndef _ARRAY_QUEUE_H_
#define _ARRAY_QUEUE_H_

#include <stdbool.h>
#include <stdint.h>

#define Q_ELEM_T    int32_t

uint8_t queue_init (void);
bool queue_full (void);
bool queue_empty (void);
uint8_t queue_push (Q_ELEM_T element);
Q_ELEM_T queue_pop (void);
void print_queue (void);
int array_queue_test (void);

#endif
