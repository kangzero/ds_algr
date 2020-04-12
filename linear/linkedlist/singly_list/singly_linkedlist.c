/********************************************************************************
 *
 * Filename: singly_linkedlist.c
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
#include "singly_linkedlist.h"

//create one node
ListNode* create_node (int val, ListNode *next)
{
	ListNode *rv = malloc(sizeof(ListNode*));
	if (rv == NULL) {
	    printf("[LINKEDLIST] New ListNode Malloc Failed!!!\n");
	    return NULL;
	}
	rv->val = val;
	rv->next = next;
	return rv;
}

//free list
void free_list (ListNode *head)
{
    ListNode *prev;
    while (head) {
        prev = head;
        head = head->next;
        free(prev);
        prev = NULL;
    }
    return;
}

//Linkedlist init
Linkedlist* linkedlist_init(void)
{
    Linkedlist *rv = calloc(1, sizeof(Linkedlist*));
    if (rv == NULL) {
        printf("[LINKEDLIST] Linkedlist init failed!\n");
	    return NULL;
    }
    return rv;
}

//get the val of index-th node,  if index is invalid, return -1
int linkedlist_get(Linkedlist* obj, size_t index)
{
    if ((obj->size) <= index){
        printf("[LINKEDLIST] Can't get at invalid index %zd!\n", index);
        return -1;
    }
    ListNode *cur = obj->head;
    for (int i = 0; i < index; i++)
        cur = cur->next;
    printf("[LINKEDLIST] element at index %zu is %d\n", index, cur->val);
    return cur->val;
}

//add a node before the head
void linkedlist_add_head(Linkedlist *obj, int val)
{
    ListNode *newnode = create_node(val, obj->head);
    obj->head = newnode;
    obj->size += 1;
    if (obj->size == 1)
        obj->tail = obj->head; //d-linked;
    return;
}

//append a node at the tail of the linked list
void linkedlist_append_tail(Linkedlist *obj, int val)
{
    ListNode *newnode = create_node(val, NULL);
    if (obj->head == NULL) {
        linkedlist_add_head(obj, val);
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
void linkedlist_insert(Linkedlist *obj, size_t index, int val)
{
    if (index > (obj->size)) {
        printf("[LINKEDLIST] Can't insert at invalid index %zd!\n", index);
        return;
    }

    if (index == 0)
        return linkedlist_add_head(obj, val);

    if (index == (obj->size))
        return linkedlist_append_tail(obj, val);

    ListNode *cur = obj->head;
    for (int i = 1; i < index; i++)
        cur = cur->next;
    ListNode *newnode = create_node(val, cur->next);
    cur->next = newnode;
    obj->size += 1;
    return;
}

// delete the idx-th node in the linked list if the index is valid
void linkedlist_delete(Linkedlist *obj, size_t index)
{
    if (index < 0 || index >= obj->size) {
        printf("[LINKEDLIST] Can't delete at invalid index %zd! \n", index);
        return;
    }

    if (index == 0) {
        ListNode *tmp = obj->head;
        obj->head = obj->head->next;
        obj->size -= 1;
        free(tmp);
        return;
    }

    if (index == obj->size - 1) {
        ListNode *tmp = obj->head;
        while (tmp->next != obj->tail)
            tmp = tmp->next;
        free(tmp->next);
        tmp->next = NULL;
        obj->tail = tmp;
        obj->size -= 1;
        return;
    }

    ListNode *tmp = obj->head;
    for (int i = 1; i < index; i++)
        tmp = tmp->next;
    ListNode *rm = tmp->next;
    tmp->next = rm->next;
    obj->size -= 1;
    free(rm);
    rm = NULL;
    return;
}

//delete linked list
void linkedlist_free (Linkedlist *obj)
{
    free_list(obj->head);
    free(obj);
    obj = NULL;
    return;
}

//print linkedlist
void print_list (Linkedlist* obj)
{
    if ((obj == NULL) || (obj->size == 0)) {
        printf("[LINKEDLIST] This is an empty linkedlist.\n");
        return;
    }
    ListNode *cur = obj->head;
    printf("[LINKEDLIST] The list is: ");
    while(cur != NULL)
    {
        printf("%d->", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
    return;
}

//print list from head node to null
void print_listnode (ListNode* head)
{
    ListNode *cur = head;
    printf("[LINKEDLIST] The elements in the list are: ");
    while(cur != NULL)
    {
        printf("%d->", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
    return;
}















