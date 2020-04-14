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
#include "slink/slink.h"
#include "list_api.h"
#include "../log.h"

int slink_test(void);

#ifdef _MODULAR_TEST
int main(int argc, char *argv[])
{
    logger_init();
    slink_test();
}
#endif

int slink_test(void)
{
    Log.i(TAG, "==== Singly Linkedlist Test Program ====\n");

    sList *testlist = slist_init();
    Log.i(TAG, "Initialized testlist, no node in list");
    print_list(testlist);

    Log.i(TAG, "Add val=1 @head");
    slist_add_head(testlist, 1);
    print_list(testlist);

    Log.i(TAG, "Append val=5 @tail");
    slist_append_tail(testlist, 5);
    print_list(testlist);

    Log.i(TAG, "Insert val=2 @index 1");
    slist_insert(testlist, 1, 2);
    print_list(testlist);

    Log.i(TAG, "Insert val=3 @index 2");
    slist_insert(testlist, 2, 3);
    print_list(testlist);

    Log.i(TAG, "Insert val=4 @index 3");
    slist_insert(testlist, 3, 4);
    print_list(testlist);

    // try to insert node into an invalid index
    Log.i(TAG, "Try to insert a node into an invalid index");
    slist_insert(testlist, -1, 100);
    slist_insert(testlist, 10, 101);
    print_list(testlist);

    Log.i(TAG, "Get element @index 2");
    slist_get(testlist, 2);

    Log.i(TAG, "Append val=6 @tail");
    slist_append_tail(testlist, 6);
    print_list(testlist); // 1->2->3->4->5->6

    Log.i(TAG, "Delete node @index 2");
    slist_delete(testlist, 2); // now 1->2->4->5->6
    print_list(testlist);

    Log.i(TAG, "Delete node @head");
    slist_delete(testlist, 0); // now 2->4->5->6
    print_list(testlist);

    Log.i(TAG, "Delete node @tail");
    slist_delete(testlist, 3); // now 2->4->5
    print_list(testlist);

    Log.i(TAG, "Get node @index 0");
    slist_get(testlist, 0);

    // try to delete node into an invalid index
    Log.i(TAG, "Try to delete a node at an invlid index");
    slist_delete(testlist, -1);
    slist_delete(testlist, 10);
    print_list(testlist);

    Log.i(TAG, "Try to get node @ an invalid index");
    slist_get(testlist, 5);
    slist_get(testlist, -10);
    print_list(testlist);

    Log.i(TAG, "List Reverse:");
    sListNode *p = list_reverse(testlist->head);
    print_listnode(p);

    Log.i(TAG, "Free list ... ...");
    slist_free(testlist);
    testlist = NULL;
    print_list(testlist);

    Log.i(TAG, "==== Linkedlist Test End ====\n");

    return 1;
}
