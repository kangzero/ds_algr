/***************************************************
 *
 * Filename: doubly_linkedlist.c
 *
 * Version: v1.0
 * History:
 * V1.0     Created by Ning kang    03/24/2019
 *
 * Copyright(c) 2019 by Ning Kang
 * This software is placed in the public domain
 * and may be used for any purpose. However, this
 * notice must not be changed or removed and no
 * warranty is either expressed or implied by its
 * publician or distribution.
 *
 **************************************************/

#include <stdio.h>
#include <malloc.h>

#include "dlink.h"
#include "../../../log.h"

#define TAG     "DLINK"

// head of the doubly linked list, no element in the head
static dNode *dl_head = NULL;
// number of nodes in the doubly linked list
static uint32_t count = 0;

static dNode* get_node (uint32_t index);

// create doubly linked list node
dNode* dlink_create_node (void *pval)
{
    dNode *pnode = NULL;
    if ((pnode = malloc(sizeof(dNode))) == NULL) {
        Log.e(TAG, "Malloc failed for creating dListNode!");
        return NULL;
    }
    // by default the prev node and next node point to itself
    pnode->prev = pnode->next = pnode;
    pnode->val = pval;

    return pnode;
}

// create a doubly linked list, return -1 if failed
uint8_t dlink_init (void)
{
    dNode *p_head = NULL;
    if ((p_head = dlink_create_node(NULL)) == NULL)
        return -1;
    // set the node to the head
    dl_head = p_head;
    // set count to 0
    count = 0;
    return 1;
}

// if the doubly linked list is empty
uint8_t dlink_is_empty (void)
{
    return count == 0;
}

// get the doubly linked list size
uint32_t dlink_size (void)
{
    return count;
}

// get the node at index
static dNode* get_node (uint32_t index)
{
    if (index < 0 || index >= count) {
        Log.w(TAG, "Invalid index for the dlink list!");
        return NULL;
    }

    // search the node from the head
    if (index <= count / 2) {
        uint32_t i = 0;
        dNode *l_node = dl_head->next;
        while (i++ < index)
            l_node = l_node->next;
        return l_node;
    }

    // search the node from the tail
    uint32_t j = 0;
    uint32_t tail_index = count - index - 1;
    dNode *r_node = dl_head->prev;
    while (j++ < tail_index)
        r_node = r_node->prev;
    return r_node;
}

// get the first node
dNode* dlink_get_first (void)
{
    return get_node(0);
}

// get the last node
dNode* dlink_get_last (void)
{
    return get_node(count-1);
}

// get the element of node in index position
void* dlink_get(uint32_t index)
{
    dNode *inode = get_node(index);
    if (!inode) {
        Log.i(TAG, "Dlink get node failed!");
        return NULL;
    }
    return inode->val;
}

uint8_t dlink_insert_first (void *pv)
{
    dNode *pnode = dlink_create_node(pv);
    if (!pnode)
        return -1;

    pnode->prev = dl_head;
    pnode->next = dl_head->next;
    dl_head->next->prev = pnode;
    dl_head->next = pnode;
    count++;

    return 0;
}

uint8_t dlink_append_last (void *pv)
{
    dNode *pnode = dlink_create_node(pv);
    if (!pnode)
        return -1;

    pnode->next = dl_head;
    pnode->prev = dl_head->prev;
    dl_head->prev->next = pnode;
    dl_head->prev = pnode;
    count++;

    return 0;
}

// insert p_val into the index position of the dlink list
uint8_t dlink_insert (uint32_t index, void *pv)
{
    if (index == 0)
        return dlink_insert_first(pv);

    if (index == count)
        return dlink_append_last(pv);

    dNode *inode = get_node(index);
    if (!inode)
        return -1;

    dNode *pnode = dlink_create_node(pv);
    if (pnode == NULL)
        return -1;
    pnode->prev = inode->prev;
    pnode->next = inode;
    inode->prev->next = pnode;
    inode->prev = pnode;
    count++;

    return 0;
}

// delete the node at index
uint8_t dlink_delete (uint32_t index)
{
    dNode *inode = get_node(index);
    if (!inode)
        return -1;

    inode->next->prev = inode->prev;
    inode->prev->next = inode->next;
    free(inode), inode = NULL;
    count--;

    return 0;
}

// delete the node at head
uint8_t dlink_delete_first(void)
{
    return dlink_delete(0);
}

// delete the node at tail
uint8_t dlink_delete_last(void)
{
    return dlink_delete(count-1);
}

// destroy the doubly linked list
uint8_t dlink_destroy(void)
{
    if (!dl_head) {
        Log.e(TAG, "Failed to destroy an empty dlink!");
        return -1;
    }

    dNode *pnode = dl_head->next;
    dNode *tmp = NULL;
    while (pnode != dl_head) {
        tmp = pnode;
        pnode = pnode->next;
        free(tmp), tmp = NULL;
    }
    free(dl_head), dl_head = NULL;
    count = 0;

    return 0;
}






