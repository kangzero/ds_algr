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

#ifndef _SLINK_H_
#define _SLINK_H_

#include <stddef.h>

#define TAG     "SLINK"

//singly linked list defnition
typedef struct sListNode_t {
    int val;
    struct sListNode_t *next;
} sListNode;

//Linkedlist definition
typedef struct sList_t {
    sListNode *head;
    sListNode *tail;
    int size;
} sList;

sList* slist_init(void);
int slist_get(sList *obj, size_t index);
void sListNode_free(sListNode *head);
void slist_add_head(sList *obj, int val);
void slist_append_tail(sList *obj, int val);
void slist_insert(sList *obj, size_t index, int val);
void slist_delete(sList *obj, size_t index);
void slist_free(sList *obj);
void print_list(sList *obj);
void print_listnode(sListNode* head);

#endif


