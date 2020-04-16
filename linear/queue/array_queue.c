#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#include "array_queue.h"
#include "../log.h"

#define TAG     "ARRAY_QUEUE"

#define QUEUE_MAX_SIZE  32U
#define ERR INT_MIN

extern int slink_queue_test(void);
extern int dlink_queue_test(void);

static Q_ELEM_T *queue = NULL;
static uint32_t count = -1;

// queue init
uint8_t queue_init (void)
{
    queue = (Q_ELEM_T*)malloc(QUEUE_MAX_SIZE * sizeof(Q_ELEM_T));
    if (!queue) {
        Log.e(TAG, "queue_init failed: out of Memory!");
        return 0;
    }
    count = 0;

    return 1;
}

// queue destroy
uint8_t queue_destroy (void)
{
    if (queue) {
        free(queue), queue = NULL;
        return 1;
    }

    return 0;
}

// queue is full
bool queue_full (void)
{
    return count == QUEUE_MAX_SIZE;
}

// queue is empty
bool queue_empty (void)
{
    return count == 0;
}

// queue push
uint8_t queue_push (Q_ELEM_T element)
{
    if (queue_full()) {
        Log.i(TAG, "queue is full!");
        return 0;
    }

    queue[count++] = element;
    return 1;
}

// queue pop
Q_ELEM_T queue_pop (void)
{
    if (queue_empty()) {
        Log.i(TAG, "It's an empty queue!");
        return ERR;
    }

    Q_ELEM_T ret = queue[0];
    count--;
    uint32_t i = 0;
    while (i++ < count) {
        queue[i-1] = queue[i];
    }

    return ret;
}

void print_queue(void)
{
    Log.i(TAG, "Print the queue from Head to Tail:");
    if (queue_empty()) {
        Log.i(TAG, "Nothing to print for an empty queue!");
        return;
    }

    for (int i = count - 1; i >= 0; i--)
        Log.i(TAG, "queue[%d] = %d", i, queue[i]);

    return;
}

#ifdef _MODULAR_TEST
int main (void) {
    logger_init();
    array_queue_test();
    slink_queue_test();
    dlink_queue_test();
}
#endif

int array_queue_test(void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

    queue_init();

    // queue push test
    Log.i(TAG, "queue push 32 elements 10 to 320 ...");
    for (int i = 0; i < QUEUE_MAX_SIZE; i++)
        queue_push(10*(i+1));
    print_queue();

    // push an element into a full queue
    Log.i(TAG, "push elements larger than the max capacity of the queue ...");
    queue_push(1000);

    //queue pop test
    Log.i(TAG, "queue pop out 2 elements ...");
    Q_ELEM_T dat = 0;
    if ((dat = queue_pop()))
        Log.i(TAG, "%d", dat);
    if ((dat = queue_pop()))
        Log.i(TAG, "%d", dat);
    print_queue();

    //queue empty test
    Log.i(TAG, "pop out elements until the queue is empty ...");
    while (!queue_empty())
        queue_pop();
    print_queue();

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}

