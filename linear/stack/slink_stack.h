#ifndef _SLINK_STACK_H_
#define _SLINK_STACK_H_

sListNode* slink_stack_push (ELEM_T val);
ELEM_T slink_stack_pop (void);
ELEM_T slink_stack_peek (void);
uint32_t slink_stack_size(void);
bool slink_stack_empty(void);
static void slink_stack_destroy (void);
int slink_stack_test(void);

#endif
