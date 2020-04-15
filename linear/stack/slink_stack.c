#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#include "../log.h"
#include "../list/slink/slink.h"
#include "slink_stack.h"

#define TAG     "SLINK_STACK"
#define ERR     INT_MIN

static void print_slink_stack(void);

// the head of the singly linked list
sListNode *sl_head = NULL;

// push element into the stack
sListNode* slink_stack_push (ELEM_T val)
{
    sListNode *pv = slink_create_node(val, NULL);
    if (!pv)
        return NULL;
    pv->next = sl_head;
    sl_head = pv;

    return sl_head;
}

// pop out element at the the stack top
ELEM_T slink_stack_pop (void)
{
    if (!sl_head) {
        Log.w(TAG, "Pop failed: this is an empty stack!");
        return ERR;
    }

    ELEM_T val;
    sListNode *rm;
    val = sl_head->val;
    rm = sl_head;
    sl_head = sl_head->next;
    free(rm);

    return val;
}

// get the val of top element
ELEM_T slink_stack_peek (void)
{
    if (!sl_head) {
        Log.w(TAG, "Peek failed: this is an empty stack!");
        return ERR;
    }

    return sl_head->val;
}

// size of the slink stack
uint32_t slink_stack_size (void)
{
    uint32_t count = 0;

    sListNode *cur = sl_head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }

    return count;
}

// is empty stack
bool slink_stack_empty (void)
{
    return sl_head == NULL;
}

// destroy the slink stack
static void slink_stack_destroy (void)
{
    sListNode *rm = NULL;

    while (sl_head != NULL) {
        rm = sl_head;
        sl_head = sl_head->next;
        free(rm), rm = NULL;
    }
}

// test interface
int slink_stack_test(void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

    ELEM_T tmp;

    Log.i(TAG, "push elements 10 - 50 into the stack");
    slink_stack_push(10);
    slink_stack_push(20);
    slink_stack_push(30);
    slink_stack_push(40);
    slink_stack_push(50);
    print_slink_stack();

    Log.i(TAG, "pop 2 elements");
    tmp = slink_stack_pop();
    Log.i(TAG, "%d", tmp);
    tmp = slink_stack_pop();
    Log.i(TAG, "%d", tmp);
    print_slink_stack();

    Log.i(TAG, "peek the top");
    tmp = slink_stack_peek();
    Log.i(TAG, "Stack top is %d", tmp);

    Log.i(TAG, "push element 100");
    slink_stack_push(100);
    print_slink_stack();

    Log.i(TAG, "destroy the stack");
    slink_stack_destroy();
    print_slink_stack();

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}

static void print_slink_stack(void)
{
    if (slink_stack_empty()) {
        Log.w(TAG, "Slink stack is empty!");
        return;
    }

    Log.i(TAG, "The slink stack size is %d", slink_stack_size());
    sListNode *cur = sl_head;
    while (cur != NULL) {
        Log.i(TAG, "%d", cur->val);
        cur = cur->next;
    }
}


