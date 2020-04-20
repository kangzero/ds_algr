#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "dlink_stack.h"
#include "../list/dlink/dlink.h"
#include "../../log.h"

#define TAG     "DLINK_STACK"

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

// init the dlink stack
uint8_t dlink_stack_init (void)
{
    return dlink_init();
}

// destroy the dlink stack
uint8_t dlink_stack_destroy (void)
{
    return dlink_destroy();
}

// dlink stack push
uint8_t dlink_stack_push (void *pv)
{
    return dlink_insert_first(pv);
}

// get the stack top element
void* dlink_stack_peek (void)
{
    dNode *node = (dNode*)dlink_get_first();
    if (!node && !node->val)
        return NULL;

    return node->val;
}

// dlink stack pop
void* dlink_stack_pop (void)
{
    void *p = dlink_stack_peek();
    dlink_delete_first();
    return p;
}

// the size of dlink stack
uint32_t dlink_stack_size (void)
{
    return dlink_size();
}

// check if the dlink stack is empty
bool dlink_stack_empty (void)
{
    return dlink_is_empty();
}

static void print_stu (stu_t *p)
{
    if (!p)
        return;

    Log.i(TAG, "Id = %d, Name = %s", p->id, p->name);
}

int dlink_stack_test (void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

    stu_t *pv = NULL;
    dlink_stack_init();

    //Log.i(TAG, "Push 8 objects into the dlink stack");
    for (int i = 0; i < STU_SIZE-1; i++) {
        dlink_stack_push(&students[i]);
    }

    pv = (stu_t*)dlink_stack_peek();
    Log.i(TAG, "The top of the stack is:");
    print_stu(pv);

    dlink_stack_push(&students[STU_SIZE-1]);
    Log.i(TAG, "Pop out elements one by one until the dlink stack is empty:");
    while (!dlink_is_empty()) {
        pv = (stu_t*)dlink_stack_pop();
        print_stu(pv);
    }

    dlink_stack_destroy();

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}
