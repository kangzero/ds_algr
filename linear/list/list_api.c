/********************************************************************************
 *
 * Filename: singly_linkedlist_op.c
 * Description: singly linkedlist operation implementation by C
 *
 * Version: v1.0
 * History:
 * V1.0     Created by Ning Kang     04/09/2019
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

#include "list_api.h"

#define RECURSIVE 1
#define ITERATIVE 0

//reverse list
sListNode* list_reverse(sListNode *head)
{
    if ((head == NULL) || (head->next == NULL))
    {
        return head;
    }

#if RECURSIVE
    sListNode *p = list_reverse(head->next);
    head->next->next = head;
    head->next = NULL;

    return p;
#elif ITERATIVE
    sListNode *cur = head;
    sListNode *pre = NULL;

    while (cur != NULL) {
        sListNode *next = cur->next;
        cur->next = pre; //reverse happens here
        pre = cur;
        cur = next;
    }

    return pre;
#endif
}

