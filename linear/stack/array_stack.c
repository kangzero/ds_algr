#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#include "array_stack.h"
#include "../log.h"

#define TAG     "ARRAY_STACK"

#define ERROR INT_MIN

extern int slink_stack_test(void);

// stack init
stack* stack_init (void)
{
    stack* p_stack = (stack*)malloc(sizeof(stack));
    if (!p_stack) {
        Log.e(TAG, "stack_init failed: out of Memory!");
        return NULL;
    }

    p_stack->top = -1;
    return p_stack;
}

// stack is full
bool stack_full (stack* p_stack)
{
    if (p_stack->top == MAX_SIZE - 1) {
        Log.i(TAG, "Stack is full!");
        return true;
    }

    return false;
}

// stack is empty
bool stack_empty (stack* p_stack)
{
    if (p_stack->top == -1) {
        Log.i(TAG, "It's an empty stack!");
        return true;
    }

    return false;
}

// stack push
void stack_push (stack* p_stack, E_TYPE element)
{
    if (stack_full(p_stack))
        return;

    p_stack->dat[++p_stack->top] = element;
}

// stack pop
E_TYPE stack_pop (stack* p_stack)
{
    if(stack_empty(p_stack))
        return ERROR;

    return p_stack->dat[p_stack->top--];
}

// stack print
void stack_print (stack* p_stack)
{
    if (stack_empty(p_stack))
        return;

    Log.i(TAG, "Elements in the stack:");
    for (int32_t i = p_stack->top; i >= 0; i--)
        Log.i(TAG, "%d", p_stack->dat[i]);
}

#ifdef _MODULAR_TEST
int main (void) {
    logger_init();
    array_stack_test();
    slink_stack_test();
}
#endif

int array_stack_test(void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

    stack* p_stack;
    p_stack = stack_init();

    //stack push test
    Log.i(TAG, "stack push 5 elements 1 ~5 :");
    stack_push(p_stack, 1);
    stack_push(p_stack, 2);
    stack_push(p_stack, 3);
    stack_push(p_stack, 4);
    stack_push(p_stack, 5);
    stack_print(p_stack);

    //stack pop test
    Log.i(TAG, "stack pop out 2 elements :");
    stack_pop(p_stack);
    stack_pop(p_stack);
    stack_print(p_stack);

    //stack full test
    Log.i(TAG, "push elements larger than the max capacity of the stack :");
    for (int i = 4; i <= MAX_SIZE; i++)
        stack_push(p_stack, i);
    stack_print(p_stack);
    stack_push(p_stack, 1025);

    //stack empty test
    Log.i(TAG, "pop out elements until the stack is empty: ");
    while (p_stack->top >= 0)
        stack_pop(p_stack);
    stack_print(p_stack);

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}

