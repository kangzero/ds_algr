#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#include "../log.h"
#include "../list/slink/slink.h"
#include "slink_queue.h"

#define TAG     "SLINK_QUEUE"
#define ERR     INT_MIN

static void print_slink_queue(void);

// the head of the singly linked list
static sListNode *q_head = NULL;

// push element into the queue
void slink_queue_push (ELEM_T val)
{
    if (!q_head) {
        q_head = slink_create_node(val, NULL);
        return;
    }

    sListNode *pv = slink_create_node(val, NULL);
    if (!pv)
        return;

    sListNode *cur = q_head;
    while (cur->next)
        cur = cur->next;
    cur->next = pv;

    return;
}

// pop out element at the the queue top
ELEM_T slink_queue_pop (void)
{
    if (!q_head) {
        Log.w(TAG, "Pop failed: this is an empty queue!");
        return ERR;
    }

    ELEM_T val;
    sListNode *rm;
    val = q_head->val;
    rm = q_head;
    q_head = q_head->next;
    free(rm), rm = NULL;

    return val;
}

// get the val of top element
ELEM_T slink_queue_peek (void)
{
    if (!q_head) {
        Log.w(TAG, "Peek failed: this is an empty queue!");
        return ERR;
    }

    return q_head->val;
}

// size of the slink queue
uint32_t slink_queue_size (void)
{
    uint32_t count = 0;

    sListNode *cur = q_head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }

    return count;
}

// is empty queue
bool slink_queue_empty (void)
{
    return q_head == NULL;
}

// destroy the slink queue
static void slink_queue_destroy (void)
{
    sListNode *rm = NULL;

    while (q_head != NULL) {
        rm = q_head;
        q_head = q_head->next;
        free(rm), rm = NULL;
    }
}

// test interface
int slink_queue_test(void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

    ELEM_T tmp;

    Log.i(TAG, "push elements 10 - 50 into the queue");
    slink_queue_push(10);
    slink_queue_push(20);
    slink_queue_push(30);
    slink_queue_push(40);
    slink_queue_push(50);
    print_slink_queue();

    Log.i(TAG, "pop 2 elements");
    tmp = slink_queue_pop();
    Log.i(TAG, "%d", tmp);
    tmp = slink_queue_pop();
    Log.i(TAG, "%d", tmp);
    print_slink_queue();

    Log.i(TAG, "peek the top");
    tmp = slink_queue_peek();
    Log.i(TAG, "queue top is %d", tmp);

    Log.i(TAG, "push element 100");
    slink_queue_push(100);
    print_slink_queue();

    Log.i(TAG, "destroy the queue");
    slink_queue_destroy();
    print_slink_queue();

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}

static void print_slink_queue(void)
{
    if (slink_queue_empty()) {
        Log.w(TAG, "Slink queue is empty!");
        return;
    }

    Log.i(TAG, "Print the queue from head to tail (size == %d)", slink_queue_size());
    sListNode *cur = q_head;
    while (cur != NULL) {
        Log.i(TAG, "%d", cur->val);
        cur = cur->next;
    }
}


