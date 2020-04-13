/********************************************************************************
 *
 * Filename: singly_list_test.c
 *
 * Version: v1.1
 * History:
 * V1.0     Created by Ning Kang                        03/20/2019
 * V1.1     Basic Linkedlist operation by Ning Kang     04/09/2019
 *
 * Copyright(c) 2019 by Ning Kang
 * This Software is places in the public domain and may be used for any purpose.
 * However, this notice must not be changed or removed and no warranty is either
 * expressed or implied by its publician or distribution.
 *
 ********************************************************************************/

#include <stdio.h>
#include <stddef.h>
#include "singly_list/singly_linkedlist.h"
#include "linkedlist_algorithms.h"
#include "../log.h"

int singly_list_test(void);

#ifdef _MODULAR_TEST
int main(int argc, char *argv[])
{
    logger_init();
    singly_list_test();
}
#endif

int singly_list_test(void)
{
    Log.i(TAG, "==== Linkedlist Test Program ====\n");

    Linkedlist *testlist = linkedlist_init();
    Log.i(TAG, "Initialized testlist, no node in list");
    print_list(testlist);

    Log.i(TAG, "Add val=1 @head");
    linkedlist_add_head(testlist, 1);
    print_list(testlist);

    Log.i(TAG, "Append val=5 @tail");
    linkedlist_append_tail(testlist, 5);
    print_list(testlist);

    Log.i(TAG, "Insert val=2 @index 1");
    linkedlist_insert(testlist, 1, 2);
    print_list(testlist);

    Log.i(TAG, "Insert val=3 @index 2");
    linkedlist_insert(testlist, 2, 3);
    print_list(testlist);

    Log.i(TAG, "Insert val=4 @index 3");
    linkedlist_insert(testlist, 3, 4);
    print_list(testlist);

    // try to insert node into an invalid index
    Log.i(TAG, "Try to insert a node into an invalid index");
    linkedlist_insert(testlist, -1, 100);
    linkedlist_insert(testlist, 10, 101);
    print_list(testlist);

    Log.i(TAG, "Get element @index 2");
    linkedlist_get(testlist, 2);

    Log.i(TAG, "Append val=6 @tail");
    linkedlist_append_tail(testlist, 6);
    print_list(testlist); // 1->2->3->4->5->6

    Log.i(TAG, "Delete node @index 2");
    linkedlist_delete(testlist, 2); // now 1->2->4->5->6
    print_list(testlist);

    Log.i(TAG, "Delete node @head");
    linkedlist_delete(testlist, 0); // now 2->4->5->6
    print_list(testlist);

    Log.i(TAG, "Delete node @tail");
    linkedlist_delete(testlist, 3); // now 2->4->5
    print_list(testlist);

    Log.i(TAG, "Get node @index 0");
    linkedlist_get(testlist, 0);

    // try to delete node into an invalid index
    Log.i(TAG, "Try to delete a node at negative index");
    linkedlist_delete(testlist, -1);
    linkedlist_delete(testlist, 10);
    print_list(testlist);

    Log.i(TAG, "Try to get node @ an invalid index");
    linkedlist_get(testlist, 5);
    linkedlist_get(testlist, -10);
    print_list(testlist);

    Log.i(TAG, "List Reverse:");
    ListNode *p = linkedlist_reverse(testlist->head);
    print_listnode(p);

    Log.i(TAG, "Free list ... ...");
    linkedlist_free(testlist);
    testlist = NULL;
    print_list(testlist);

    Log.i(TAG, "==== Linkedlist Test End ====\n");

    return 1;
}
