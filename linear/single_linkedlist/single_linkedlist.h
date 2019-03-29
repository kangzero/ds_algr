/********************************************************************************
 *
 * Filename: single_linkedlist.h
 * Description: single linkedlist head file
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

#ifndef SINGLE_LINKEDLIST_H
#define SINGLE_LINKEDLIST_H

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
Linkedlist* linkedlist_init();
int linkedlist_get (Linkedlist* obj, size_t index);
void free_list (ListNode *head);
void linkedlist_add_at_head (Linkedlist *obj, int val);
void linkedlist_append_at_tail (Linkedlist *obj, int val);
void linkedlist_insert_at_index (Linkedlist *obj, size_t index, int val);
void linkedlist_delete_at_index (Linkedlist *obj, size_t index);
void linkedlist_free (Linkedlist *obj);
void print_list (Linkedlist *obj);

#endif


