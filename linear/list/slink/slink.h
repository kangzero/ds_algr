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
#include <stdint.h>

#define ELEM_T    uint32_t

//singly linked list defnition
typedef struct sListNode_t {
    ELEM_T val;
    struct sListNode_t *next;
} sListNode;

//Linkedlist definition
typedef struct sList_t {
    sListNode *head;
    sListNode *tail;
    uint32_t size;
} sList;


sList* slist_init(void);
sListNode* slink_create_node(ELEM_T val, sListNode *next);
ELEM_T slist_get(sList *obj, size_t index);
void sListNode_free(sListNode *head);
void slist_add_head(sList *obj, ELEM_T val);
void slist_append_tail(sList *obj, ELEM_T val);
void slist_insert(sList *obj, size_t index, ELEM_T val);
void slist_delete(sList *obj, size_t index);
void slist_free(sList *obj);
void print_list(sList *obj);
void print_listnode(sListNode* head);

#endif


