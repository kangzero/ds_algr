/************************************************
 *
 * Filename: testbench.c
 *
 * Version: v1.0
 * History:
 * V1.0     Created by Ning Kang     03/20/2019
 *
 * Copyright(c) 2019 by Ning Kang
 * This Software is places in the public domain
 * and may be used for any purpose. However, this
 * notice must not be changed or removed and no
 * warranty is either expressed or implied by its
 * publician or distribution.
 *
 ************************************************/

#include <stdio.h>
#include "single_linkedlist.h"

int main(int argc, char *argv[])
{
    Linkedlist *testlist = linkedlist_init();
    printf("0: uninitialized testlist... \n");
    print_list(testlist);

    printf("1. add 1 @ head...\n");
    linkedlist_add_at_head(testlist, 1);
    print_list(testlist);
    printf("2. append 5 @ tail...\n");
    linkedlist_append_at_tail(testlist, 5);
    print_list(testlist);

    printf("3. insert 2 @index 1...\n");
    linkedlist_insert_at_index(testlist, 1, 2);
    print_list(testlist);
    printf("4. insert 3 @index 2...\n");
    linkedlist_insert_at_index(testlist, 2, 3);
    print_list(testlist);
    printf("5. insert 4 @index 3...\n");
    linkedlist_insert_at_index(testlist, 3, 4);
    print_list(testlist);

    printf("6. get element @index 2... \n");
    linkedlist_get(testlist, 2);

    printf("7. append 6 @ tail...\n");
    linkedlist_append_at_tail(testlist, 6);
    print_list(testlist); // 1->2->3->4->5->6

    printf("8. delete element @ index 2...\n");
    linkedlist_delete_at_index(testlist, 2); // now 1->2->4->5->6
    print_list(testlist);

    printf("9. delete element @ head...\n");
    linkedlist_delete_at_index(testlist, 0); // now 2->4->5->6
    print_list(testlist);

    printf("10. delete element @ tail...\n");
    linkedlist_delete_at_index(testlist, 3); // now 2->4->5
    print_list(testlist);

    printf("11. get element @ index 0...\n");
    linkedlist_get(testlist, 0);

    //printf("12. insert element @ invalid index...\n");
    //linkedlist_insert_at_index(testlist, 3, 10000);
    //print_list(testlist);
    //linkedlist_insert_at_index(testlist, 5, 10000);

    //printf("13. get element @ invalid index...\n");
    //linkedlist_get(testlist, 5);

    printf("14. delete element @ invalid index...\n");
    linkedlist_delete_at_index(testlist, 5);

    printf("15. free list...\n");
    linkedlist_free(testlist);
    testlist = NULL;
    print_list(testlist);

    return 1;
}
