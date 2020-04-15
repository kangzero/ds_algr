#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_SIZE    64UL
#define E_TYPE      int32_t

typedef struct stack_ {
    //E_TYPE* dat;
    E_TYPE dat[MAX_SIZE];
    int32_t top;
} stack;

stack* stack_init(void);
bool stack_full(stack* p_stack);
bool stack_empty(stack* p_stack);
void stack_push(stack* p_stack, E_TYPE element);
E_TYPE stack_pop(stack* p_stack);
void stack_print(stack* p_stack);
int array_stack_test(void);

#endif
