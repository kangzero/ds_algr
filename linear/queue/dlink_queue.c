#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "dlink_queue.h"
#include "../list/dlink/dlink.h"
#include "../log.h"

#define TAG     "DLINK_QUEUE"

typedef struct {
    int id;
    char name[32];
} stu_t;

static stu_t students[] = {
    {111577912, "William"},
    {111577913, "James"},
    {111577914, "Harper"},
    {111577915, "Mason"},
    {111577916, "Evelyn"},
    {111577917, "Ella"},
    {111577918, "Avery"},
    {111577919, "Scarlett"}
};

#define STU_SIZE    ((sizeof(students)) / (sizeof(students[0])))

static void print_stu(stu_t *p);

// init the dlink queue
uint8_t dlink_queue_init (void)
{
    return dlink_init();
}

// destroy the dlink queue
uint8_t dlink_queue_destroy (void)
{
    return dlink_destroy();
}

// dlink queue push
uint8_t dlink_queue_push (void *pv)
{
    return dlink_append_last(pv);
}

// get the queue top element
void* dlink_queue_peek (void)
{
    dNode *node = (dNode*)dlink_get_first();
    if (!node && !node->val)
        return NULL;

    return node->val;
}

// dlink queue pop
void* dlink_queue_pop (void)
{
    void *p = dlink_queue_peek();
    dlink_delete_first();
    return p;
}

// the size of dlink queue
uint32_t dlink_queue_size (void)
{
    return dlink_size();
}

// check if the dlink queue is empty
bool dlink_queue_empty (void)
{
    return dlink_is_empty();
}

static void print_stu (stu_t *p)
{
    if (!p)
        return;

    Log.i(TAG, "Id = %d, Name = %s", p->id, p->name);
}

int dlink_queue_test (void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

    stu_t *pv = NULL;
    dlink_queue_init();

    //Log.i(TAG, "Push 8 objects into the dlink queue");
    for (int i = 0; i < STU_SIZE-1; i++) {
        dlink_queue_push(&students[i]);
    }

    pv = (stu_t*)dlink_queue_peek();
    Log.i(TAG, "The head of the queue is:");
    print_stu(pv);

    dlink_queue_push(&students[STU_SIZE-1]);
    Log.i(TAG, "Pop out elements one by one until the dlink queue is empty:");
    while (!dlink_is_empty()) {
        pv = (stu_t*)dlink_queue_pop();
        print_stu(pv);
    }

    dlink_queue_destroy();

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}
