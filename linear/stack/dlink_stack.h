#ifndef _DLINK_STACK_H_
#define _DLINK_STACK_H_

uint8_t dlink_stack_init (void);
uint8_t dlink_stack_destroy (void);
uint8_t dlink_stack_push (void *pv);
void* dlink_stack_peek (void);
void* dlink_stack_pop (void);
uint32_t dlink_stack_size (void);
bool dlink_stack_empty (void);
int dlink_stack_test (void);

#endif
