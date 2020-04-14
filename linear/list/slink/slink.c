/********************************************************************************
 *
 * Filename: slink.c
 * Description: singly linkedlist implementation by C
 *
 * Version: v1.0
 * History:
 * V1.0     Created by Ning Kang     03/19/2019
 *
 * Copyright(c) 2019 by Ning Kang
 *
 * This software is placed into the public domain and may be used for any purpose.
 * However, this notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 *
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "slink.h"
#include "../../log.h"

static sListNode* create_node(int val, sListNode *next);

// create one node
static sListNode* create_node(int val, sListNode *next)
{
	sListNode *rv = malloc(sizeof(sListNode*));
	if (rv == NULL) {
	    Log.e(TAG, "New ListNode Malloc Failed!");
	    return NULL;
	}
	rv->val = val;
	rv->next = next;
	return rv;
}

// free list
void sListNode_free(sListNode *head)
{
    sListNode *prev;
    while (head) {
        prev = head;
        head = head->next;
        free(prev);
        prev = NULL;
    }
    return;
}

// Linkedlist init
sList* slist_init(void)
{
    sList *rv = calloc(1, sizeof(sList*));
    if (rv == NULL) {
        Log.e(TAG, "Linkedlist init failed!");
	    return NULL;
    }
    return rv;
}

// get the val of index-th node,  if index is invalid, return -1
int slist_get(sList* obj, size_t index)
{
    if ((obj->size) <= index) {
        Log.w(TAG, "Can't get at invalid index %zd!", index);
        return -1;
    }
    sListNode *cur = obj->head;
    for (int i = 0; i < index; i++)
        cur = cur->next;
    Log.i(TAG, "Element at index %zu is %d", index, cur->val);
    return cur->val;
}

// add a node before the head
void slist_add_head(sList *obj, int val)
{
    sListNode *newnode = create_node(val, obj->head);
    obj->head = newnode;
    obj->size += 1;
    if (obj->size == 1)
        obj->tail = obj->head; //d-linked;
    return;
}

// append a node at the tail of the linked list
void slist_append_tail(sList *obj, int val)
{
    sListNode *newnode = create_node(val, NULL);
    if (obj->head == NULL) {
        slist_add_head(obj, val);
    } else if ((obj->head != NULL) && (obj->tail == NULL)) {
        obj->tail = newnode;
        obj->size += 1;
    } else if (obj->tail != NULL) {
        obj->tail->next = newnode;
        obj->tail = newnode;
        obj->size += 1;
    }
    return;
}

// add a node before the idx-th node in the linked list
// if idx == len of the linked list, append it to the end
// if idx > len of the linked list, do nothing
void slist_insert(sList *obj, size_t index, int val)
{
    if (index > (obj->size)) {
        Log.w(TAG, "Can't insert at invalid index %zd!", index);
        return;
    }

    if (index == 0)
        return slist_add_head(obj, val);

    if (index == (obj->size))
        return slist_append_tail(obj, val);

    sListNode *cur = obj->head;
    for (int i = 1; i < index; i++)
        cur = cur->next;
    sListNode *newnode = create_node(val, cur->next);
    cur->next = newnode;
    obj->size += 1;
    return;
}

// delete the idx-th node in the linked list if the index is valid
void slist_delete(sList *obj, size_t index)
{
    if (index < 0 || index >= obj->size) {
        Log.w(TAG, "Can't delete at invalid index %zd!", index);
        return;
    }

    if (index == 0) {
        sListNode *tmp = obj->head;
        obj->head = obj->head->next;
        obj->size -= 1;
        free(tmp);
        return;
    }

    if (index == obj->size - 1) {
        sListNode *tmp = obj->head;
        while (tmp->next != obj->tail)
            tmp = tmp->next;
        free(tmp->next);
        tmp->next = NULL;
        obj->tail = tmp;
        obj->size -= 1;
        return;
    }

    sListNode *tmp = obj->head;
    for (int i = 1; i < index; i++)
        tmp = tmp->next;
    sListNode *rm = tmp->next;
    tmp->next = rm->next;
    obj->size -= 1;
    free(rm);
    rm = NULL;
    return;
}

// delete linked list
void slist_free(sList *obj)
{
    sListNode_free(obj->head);
    free(obj);
    obj = NULL;
    return;
}

// print linkedlist
void print_list(sList* obj)
{
    if ((obj == NULL) || (obj->size == 0)) {
        Log.w(TAG,"This is an empty linkedlist.");
        return;
    }
    sListNode *cur = obj->head;
    Log.c(TAG, "The list is: ");
    while(cur != NULL) {
        printf("%d->", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
    return;
}

// print list from head node to null
void print_listnode (sListNode* head)
{
    sListNode *cur = head;
    Log.c(TAG, "The elements in the list are: ");
    while(cur != NULL) {
        printf("%d->", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
    return;
}















