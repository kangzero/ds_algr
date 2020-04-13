/********************************************************************************
 *
 * Filename: singly_linkedlist.h
 * Description: singly linkedlist head file
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

#ifndef _SINGLY_LINKEDLIST_H_
#define _SINGLY_LINKEDLIST_H_

#include <stddef.h>

#define TAG     "SINGLYLIST"
//ListNode defnition
typedef struct node {
    int val;
    struct node *next;
} ListNode;

//Linkedlist definition
typedef struct list {
    ListNode *head;
    ListNode *tail;
    int size;
} Linkedlist;

ListNode* create_node (int val, ListNode *next);
Linkedlist* linkedlist_init(void);
int linkedlist_get (Linkedlist* obj, size_t index);
void free_list (ListNode *head);
void linkedlist_add_head (Linkedlist *obj, int val);
void linkedlist_append_tail (Linkedlist *obj, int val);
void linkedlist_insert (Linkedlist *obj, size_t index, int val);
void linkedlist_delete (Linkedlist *obj, size_t index);
void linkedlist_free (Linkedlist *obj);
void print_list (Linkedlist *obj);
void print_listnode (ListNode* head);

#endif


