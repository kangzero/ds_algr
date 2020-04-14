/********************************************************************************
 *
 * Filename: list_test.c
 *
 * Version: v1.1
 * History:
 *
 * Copyright(c) 2019 by Ning Kang
 * This Software is places in the public domain and may be used for any purpose.
 * However, this notice must not be changed or removed and no warranty is either
 * expressed or implied by its publician or distribution.
 *
 ********************************************************************************/

#include <stdio.h>
#include <stddef.h>

#include "dlink/dlink.h"
#include "slink/slink.h"
#include "staticlist/staticlist.h"

#include "list_api.h"
#include "../log.h"

#define TAG     "LINKEDLIST"

int slink_test(void);
int dlink_test(void);

#ifdef _MODULAR_TEST
int main(int argc, char *argv[])
{
    logger_init();
    slink_test();
    dlink_test();
    static_list_test();
}
#endif

int slink_test(void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

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

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}

typedef struct {
    int id;
    char name[16];
} employee_t;

static employee_t employee[7] = {
    {11531624, "Leon"},
    {11531625, "John"},
    {11531626, "Peter"},
    {11531627, "Britny"},
    {11531628, "Emma"},
    {11531629, "Daisy"},
    {11531630, "Sarah"},
};

int dlink_test(void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

    Log.i(TAG, "Int test:");
    int arr[7] = {10, 20, 30, 40, 50, 60, 70};
    dlink_init();
    dlink_insert(0, &arr[5]);
    dlink_insert(0, &arr[4]);
    dlink_insert(0, &arr[1]);
    dlink_insert_first(&arr[0]);
    dlink_append_last(&arr[6]);
    dlink_insert(2, &arr[2]);
    dlink_insert(3, &arr[3]);

    Log.i(TAG, "Is emtpy dlink: %d", dlink_is_empty());
    uint32_t sz = dlink_size();
    Log.i(TAG, "Dlink size is: %d", sz);

    uint32_t *p = NULL;
    // print the elements in the dlink
    for (int i = 0; i < sz; i++) {
        if ((p = (int*)dlink_get(i)) != NULL)
            Log.i(TAG, "dNode[%d] == %d", i, *p);
    }
    Log.i(TAG, "Try to insert node into an invalid index position");
    dlink_insert(-1, &arr[0]);
    dlink_insert(100, &arr[0]);

    if(dlink_destroy() == 0)
        Log.i(TAG, "Dlink list destroyed!");
    else
        Log.i(TAG, "Dlink list destroy failed!");

    Log.i(TAG, "Dlink status: is_empty = %d, size = %d", dlink_is_empty(), dlink_size());

    Log.i(TAG, "String test");
    char *str[7] = {"avocado", "banana", "cherry", "durian", "emblic", "fig", "grape"};
    dlink_init();
    dlink_insert(0, str[1]);
    dlink_insert(0, str[4]);
    dlink_insert(0, str[5]);
    dlink_insert_first(str[0]);
    dlink_append_last(str[6]);
    dlink_insert(2, str[3]);
    dlink_insert(3, str[2]);

    Log.i(TAG, "Is emtpy dlink: %lu", dlink_is_empty());
    sz = dlink_size();
    Log.i(TAG, "Dlink size is: %d", sz);

    char *s = NULL;
    // print the elements in the dlink
    for (int i = 0; i < sz; i++) {
        if ((s = (char*)dlink_get(i)) != NULL)
            Log.i(TAG, "dNode[%d] == %s", i, s);
    }

    if(dlink_destroy() == 0)
        Log.i(TAG, "Dlink list destroyed!");
    else
        Log.i(TAG, "Dlink list destroy failed!");

    Log.i(TAG, "Object test");
    dlink_init();
    dlink_insert(0, &employee[5]);
    dlink_insert(0, &employee[4]);
    dlink_insert(0, &employee[1]);
    dlink_insert_first(&employee[0]);
    dlink_append_last(&employee[6]);
    dlink_insert(2, &employee[2]);
    dlink_insert(3, &employee[3]);

    Log.i(TAG, "Is emtpy dlink: %d", dlink_is_empty());
    sz = dlink_size();
    Log.i(TAG, "Dlink size is: %d", sz);

    employee_t *ptr = NULL;
    // print the elements in the dlink
    for (int i = 0; i < sz; i++) {
        if ((ptr = (employee_t*)dlink_get(i)) != NULL)
            Log.i(TAG, "dNode[%d] == [%d, %s]", i, ptr->id, ptr->name);
    }

    if(dlink_destroy() == 0)
        Log.i(TAG, "Dlink list destroyed!");
    else
        Log.i(TAG, "Dlink list destroy failed!");

    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}
