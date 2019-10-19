#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include "array_stack.h"

#define ERROR INT_MIN

//stack init
stack* stack_init(void)
{
    stack* p_stack;

    p_stack = (stack*)malloc(sizeof(stack));
    if (!p_stack) {
        printf("[stack_init] - Out of Memory! \n");
        return NULL;
    }
    p_stack->top = -1;

    return p_stack;
}

//stack is full
bool stack_full(stack* p_stack)
{
    if (p_stack->top == (MAX_SIZE - 1)) {
        printf("[stack_full] - Stack is full! \n");
        return true;
    }
    return false;
}

//stack is empty
bool stack_empty(stack* p_stack)
{
    if (p_stack->top == -1) {
        printf("[stack_empty] - It's an empty stack! \n");
        return true;
    }
    return false;
}

//stack push
void stack_push(stack* p_stack, E_TYPE element)
{
    if (stack_full(p_stack))
        return;

    p_stack->dat[++p_stack->top] = element;
}

//stack pop
E_TYPE stack_pop(stack* p_stack)
{
    if(stack_empty(p_stack))
        return ERROR;

    return p_stack->dat[p_stack->top--];
}

//stack print
void stack_print(stack* p_stack)
{
    if (stack_empty(p_stack)) {
        return;
    }

    printf("Elements in the stack: \n");
    for (int32_t i = p_stack->top; i >= 0; i--)
        printf("%d \n", p_stack->dat[i]);
}

void main(void)
{
    stack* p_stack;
    p_stack = stack_init();

    //stack push test
    printf("stack push test ... ... ... \n");
    stack_push(p_stack, 1);
    stack_push(p_stack, 2);
    stack_push(p_stack, 3);
    stack_push(p_stack, 4);
    stack_push(p_stack, 5);
    stack_print(p_stack);

    //stack pop test
    printf("stack pop test ... ... ... \n");
    stack_pop(p_stack);
    stack_pop(p_stack);
    stack_print(p_stack);

    //stack full test
    printf("stack full test ... ... ... \n");
    for (int i = 4; i <= MAX_SIZE; i++)
        stack_push(p_stack, i);
    stack_print(p_stack);
    stack_push(p_stack, 1025);

    //stack empty test
    printf("stack empty test ... ... ... \n");
    while (p_stack->top >= 0)
        stack_pop(p_stack);
    stack_print(p_stack);

    return;
}
