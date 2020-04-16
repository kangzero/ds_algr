#ifndef _SLINK_QUEUE_H_
#define _SLINK_QUEUE_H_

void  slink_queue_push (ELEM_T val);
ELEM_T slink_queue_pop (void);
ELEM_T slink_queue_peek (void);
uint32_t slink_queue_size(void);
bool slink_queue_empty(void);
static void slink_queue_destroy (void);
int slink_queue_test(void);

#endif
