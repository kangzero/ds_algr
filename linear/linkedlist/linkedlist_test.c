/********************************************************************************
 *
 * Filename: linkedlist_test.c
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

#ifdef _FULL_SYS
int linkedlist_test(void);

int linkedlist_test(void)
#elif defined _MODULAR_TEST
int main(int argc, char *argv[])
#endif
{
    printf("\n==== Linkedlist Test Program ====\n\n");

    Linkedlist *testlist = linkedlist_init();
    printf("[LINKEDLIST] Initialized testlist, no node in list\n");
    print_list(testlist);

    printf("[LINKEDLIST] Add node 1 @ head...\n");
    linkedlist_add_head(testlist, 1);
    print_list(testlist);

    printf("[LINKEDLIST] Append node 5 @ tail...\n");
    linkedlist_append_tail(testlist, 5);
    print_list(testlist);

    printf("[LINKEDLIST] Insert node 2 @index 1...\n");
    linkedlist_insert(testlist, 1, 2);
    print_list(testlist);

    printf("[LINKEDLIST] Insert node 3 @index 2...\n");
    linkedlist_insert(testlist, 2, 3);
    print_list(testlist);

    printf("[LINKEDLIST] Insert node 4 @index 3...\n");
    linkedlist_insert(testlist, 3, 4);
    print_list(testlist);

    // try to insert node into an invalid index
     printf("[LINKEDLIST] Try to insert a node into an invalid index:\n");
    linkedlist_insert(testlist, -1, 100);
    linkedlist_insert(testlist, 10, 101);
    print_list(testlist);

    printf("[LINKEDLIST] Get element @index 2... \n");
    linkedlist_get(testlist, 2);

    printf("[LINKEDLIST] Append node 6 @ tail...\n");
    linkedlist_append_tail(testlist, 6);
    print_list(testlist); // 1->2->3->4->5->6

    printf("[LINKEDLIST] Delete node @ index 2...\n");
    linkedlist_delete(testlist, 2); // now 1->2->4->5->6
    print_list(testlist);

    printf("[LINKEDLIST] Delete node @ head...\n");
    linkedlist_delete(testlist, 0); // now 2->4->5->6
    print_list(testlist);

    printf("[LINKEDLIST] Delete node @ tail...\n");
    linkedlist_delete(testlist, 3); // now 2->4->5
    print_list(testlist);

    printf("[LINKEDLIST] Get node @ index 0...\n");
    linkedlist_get(testlist, 0);

    // try to delete node into an invalid index
     printf("[LINKEDLIST] Try to delete a node at negative index:\n");
    linkedlist_delete(testlist, -1);
    linkedlist_delete(testlist, 10);
    print_list(testlist);

    printf("[LINKEDLIST] Try to get node @ invalid index...\n");
    linkedlist_get(testlist, 5);
    linkedlist_get(testlist, -10);
    print_list(testlist);

    printf("[LINKEDLIST] List Reverse test\n");
    ListNode *p = linkedlist_reverse(testlist->head);
    print_listnode(p);

    printf("[LINKEDLIST] Free list ... ...\n");
    linkedlist_free(testlist);
    testlist = NULL;
    print_list(testlist);

    return 1;
}
