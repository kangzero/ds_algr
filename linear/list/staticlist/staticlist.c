#include <stdio.h>
#include <stdlib.h>

#include "../../../log.h"

#define TAG     "STATICLIST"
#define MAX_SIZE 20U

typedef int elemType;

// static Linkedlist structure
typedef struct {
    elemType data;  //data
    int cur;    //cursor to next node, 0: no next node
} component, sLinkedList[MAX_SIZE];

void init_cur (sLinkedList *L);
static int sLinkedList_malloc (sLinkedList *L);
static void sLinkedList_free (sLinkedList *L, int idx);

/* init the unused nodes
 * 1. the first address of the array is the head of list
 * 2. initilized list: the cursor of node point to the next node
 * 3. the cursor of last node is 0 means the tail of the list
 *
 */
void init_cur (sLinkedList *L)
{
    for (int i = 0; i < MAX_SIZE-1; i++) {
        (*L)[i].cur = i + 1;
    }
    (*L)[MAX_SIZE-1].cur = 0;
}

// private malloc
static int sLinkedList_malloc (sLinkedList *L)
{
    int tmp = (*L)[0].cur;
    if (tmp == 0) {
        Log.w(TAG, "Static linked list malloc failed!");
    } else {
        (*L)[0].cur = (*L)[tmp].cur;
    }
    Log.i(TAG, "Mallocate %d", tmp);
    return tmp;
}

static void sLinkedList_free (sLinkedList *L, int idx)
{
    (*L)[idx].cur = (*L)[0].cur;
    (*L)[0].cur = idx;
    Log.i(TAG, "Free %d", idx);
}

int static_list_test (void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);
    sLinkedList sl;
    init_cur(&sl);
    for (int j = 0; j < MAX_SIZE; j++)
        Log.i(TAG, "the cursor of %d is %d", j, sl[j].cur);
    for (int i = 0; i < MAX_SIZE; i++) {
        int j = sLinkedList_malloc(&sl);
        if (j != 0)
            sl[j].data = 0x55;
        else
            Log.i(TAG, "the static linkedlist is full");
    }
    sLinkedList_free(&sl, 20);
    sLinkedList_malloc(&sl);

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 0;
}
