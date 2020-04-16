#ifndef _DLINK_QUEUE_H_
#define _DLINK_QUEUE_H_

uint8_t dlink_queue_init (void);
uint8_t dlink_queue_destroy (void);
uint8_t dlink_queue_push (void *pv);
void* dlink_queue_peek (void);
void* dlink_queue_pop (void);
uint32_t dlink_queue_size (void);
bool dlink_queue_empty (void);
int dlink_queue_test (void);

#endif
